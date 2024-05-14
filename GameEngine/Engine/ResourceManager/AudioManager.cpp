//#include <xaudio2.h>
#include <vector>
#include <memory>
#include<unordered_map>
#include "AudioManager.h"

namespace AudioManager
{
    //XAudio本体
    IXAudio2* pXAudio = nullptr;

    //マスターボイス
    IXAudio2MasteringVoice* pMasteringVoice = nullptr;

    ////ファイル毎に必要な情報
    //struct AudioData
    //{
    //    //サウンド情報
    //    XAUDIO2_BUFFER buf = {};
    //
    //    //ソースボイス
    //    std::unique_ptr<IXAudio2SourceVoice*[]> pSourceVoice = nullptr;
    //
    //    //同時再生最大数
    //    int svNum;
    //
    //    //ファイル名
    //    std::string fileName;
    //};

    std::unordered_map<std::string, std::shared_ptr<AudioData>> audioDatas_;
    std::vector<AudioData>	audioDatas;


    //std::unique_ptr<char[]> pBuffer;

//初期化
    void AudioManager::Initialize()
    {
        CoInitializeEx(0, COINIT_MULTITHREADED);

        XAudio2Create(&pXAudio);
        HRESULT hr;
        hr = pXAudio->CreateMasteringVoice(&pMasteringVoice);
        if (FAILED(hr))
        {
            MessageBox(NULL, L"マスタリングボイズの作成に失敗しました", L"エラー", MB_OK);
            //return hr;
        }
    }

    int AudioManager::Load(const std::string& fileName, bool loopFlag, float volume, int svNum)
    {
        //すでに同じファイルを使ってないかチェック
        for (int i = 0; i < audioDatas.size(); i++)
        {
            if (audioDatas[i].fileName == fileName)
            {
                return i;
            }
        }
        //チャンク構造体
        struct Chunk
        {
            char    id[5];      // ID
            unsigned int    size;   // サイズ
        };
        //ファイルを開く
        HANDLE hFile;
        hFile = CreateFileA(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        DWORD dwBytes = 0;
        Chunk riffChunk;
        ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL);
        ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL);
        char wave[4];
        ReadFile(hFile, &wave, 4, &dwBytes, NULL);
        Chunk formatChunk;
        while (formatChunk.id[0] != 'f') {
            if (ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL) == FALSE)
                return -1;
        }
        ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL);
        //フォーマットを読み取る
        //https://learn.microsoft.com/ja-jp/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
        WAVEFORMATEX fmt;
        ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL);        //形式
        ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL);         //チャンネル（モノラル/ステレオ）
        ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL);    //サンプリング数
        ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL);   //1秒あたりのバイト数
        ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL);       //ブロック配置
        ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL);    //サンプル当たりのビット数

        //波形データの読み込み
        Chunk data = { 0 };
        while (data.id[0] != 'd')
        {
            if (ReadFile(hFile, &data.id, 4, &dwBytes, NULL) == FALSE)
                return -1;
            if (data.id[0] == 'd' || data.id[1] == 'a')
                break;
            else
            {
                //サイズ調べて
                ReadFile(hFile, &data.size, 4, &dwBytes, NULL);
                std::unique_ptr<char[]> pBuffer = std::make_unique<char[]>(data.size); //無駄に読み込む 
                ReadFile(hFile, pBuffer.get(), data.size, &dwBytes, NULL);
            }
        }
        ReadFile(hFile, &data.size, 4, &dwBytes, NULL);
        char* pBuffer_ = new char[data.size];
        //std::unique_ptr<char[]> pBuffer;
        //pBuffer = std::make_unique<char[]>(data.size);
        //std::unique_ptr<char[]> pBuffer(new char[data.size]);
        //ReadFile(hFile, pBuffer.get(), data.size, &dwBytes, NULL);
        ReadFile(hFile, pBuffer_, data.size, &dwBytes, NULL);
        CloseHandle(hFile);
        AudioData ad;
        ad.fileName = fileName;
        //ad.buf.pAudioData = (BYTE*)std::move(pBuffer).get();
        ad.buf.pAudioData = (BYTE*)std::move(pBuffer_);
        if (loopFlag)
        {
            ad.buf.LoopCount = XAUDIO2_LOOP_INFINITE;
        }
        ad.buf.Flags = XAUDIO2_END_OF_STREAM;
        ad.buf.AudioBytes = data.size;
        //ad.buf.LoopCount = XAUDIO2_LOOP_INFINITE;
        ad.pSourceVoice = std::make_unique<IXAudio2SourceVoice * []>(svNum);

        for (int i = 0; i < svNum; i++)
        {
            HRESULT hr;
            hr = pXAudio->CreateSourceVoice(&ad.pSourceVoice[i], &fmt);

            if (volume)
                if (FAILED(hr))
                {
                    MessageBox(NULL, L"オーディオの読み込みに失敗しました", L"エラー", MB_OK);
                    //return hr;
                }
        }
        ad.svNum = svNum;

        audioDatas.push_back(std::move(ad));
        //SAFE_DELETE_ARRAY(pBuffer);
        return (int)audioDatas.size() - 1;
    }

    std::shared_ptr<AudioData> AudioManager::Load_Component(const std::string& fileName, bool loopFlag, float volume, int svNum)
    {
        //すでに同じファイルを使ってないかチェック
        if (auto itr = audioDatas_.find(fileName); itr != audioDatas_.end())
        {
            return itr->second;
        }
        //チャンク構造体
        struct Chunk
        {
            char    id[5];      // ID
            unsigned int    size;   // サイズ
        };
        //ファイルを開く
        HANDLE hFile;
        hFile = CreateFileA(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        DWORD dwBytes = 0;
        Chunk riffChunk;
        ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL);
        ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL);
        char wave[4];
        ReadFile(hFile, &wave, 4, &dwBytes, NULL);
        Chunk formatChunk;
        while (formatChunk.id[0] != 'f') {
            if (ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL) == FALSE)
                return nullptr;
        }
        ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL);
        //フォーマットを読み取る
        //https://learn.microsoft.com/ja-jp/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
        WAVEFORMATEX fmt;
        ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL);        //形式
        ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL);         //チャンネル（モノラル/ステレオ）
        ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL);    //サンプリング数
        ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL);   //1秒あたりのバイト数
        ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL);       //ブロック配置
        ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL);    //サンプル当たりのビット数

        //波形データの読み込み
        Chunk data = { 0 };
        while (data.id[0] != 'd')
        {
            if (ReadFile(hFile, &data.id, 4, &dwBytes, NULL) == FALSE)
                return nullptr;
            if (data.id[0] == 'd' || data.id[1] == 'a')
                break;
            else
            {
                //サイズ調べて
                ReadFile(hFile, &data.size, 4, &dwBytes, NULL);
                std::unique_ptr<char[]> pBuffer = std::make_unique<char[]>(data.size); //無駄に読み込む 
                ReadFile(hFile, pBuffer.get(), data.size, &dwBytes, NULL);
            }
        }
        ReadFile(hFile, &data.size, 4, &dwBytes, NULL);
        char* pBuffer_ = new char[data.size];
        //std::unique_ptr<char[]> pBuffer;
        //pBuffer = std::make_unique<char[]>(data.size);
        //std::unique_ptr<char[]> pBuffer(new char[data.size]);
        //ReadFile(hFile, pBuffer.get(), data.size, &dwBytes, NULL);
        ReadFile(hFile, pBuffer_, data.size, &dwBytes, NULL);
        CloseHandle(hFile);
        std::shared_ptr<AudioData> ad=std::make_shared<AudioData>();
        ad->fileName = fileName;
        //ad.buf.pAudioData = (BYTE*)std::move(pBuffer).get();
        ad->buf.pAudioData = (BYTE*)std::move(pBuffer_);
        if (loopFlag)
        {
            ad->buf.LoopCount = XAUDIO2_LOOP_INFINITE;
        }
        ad->buf.Flags = XAUDIO2_END_OF_STREAM;
        ad->buf.AudioBytes = data.size;
        //ad.buf.LoopCount = XAUDIO2_LOOP_INFINITE;
        ad->pSourceVoice = std::make_unique<IXAudio2SourceVoice * []>(svNum);

        for (int i = 0; i < svNum; i++)
        {
            HRESULT hr;
            hr = pXAudio->CreateSourceVoice(&ad->pSourceVoice[i], &fmt);

            if (volume)
                if (FAILED(hr))
                {
                    MessageBox(NULL, L"オーディオの読み込みに失敗しました", L"エラー", MB_OK);
                    //return hr;
                }
        }
        ad->svNum = svNum;

        audioDatas_.insert({ fileName,ad });
            //SAFE_DELETE_ARRAY(pBuffer);
        return ad;
    }

    //再生
    void AudioManager::Play(int ID)
    {
        for (int i = 0; i < audioDatas[ID].svNum; i++)
        {
            XAUDIO2_VOICE_STATE state;
            audioDatas[ID].pSourceVoice[i]->GetState(&state);

            if (state.BuffersQueued == 0)
            {
                audioDatas[ID].pSourceVoice[i]->SubmitSourceBuffer(&audioDatas[ID].buf);
                audioDatas[ID].pSourceVoice[i]->Start();
                break;
            }
        }
    }

    void AudioManager::Stop(int ID)
    {
        for (int i = 0; i < audioDatas[ID].svNum; i++)
        {
            audioDatas[ID].pSourceVoice[i]->Stop();
            audioDatas[ID].pSourceVoice[i]->FlushSourceBuffers();
        }
    }

    void AudioManager::SetVolume(int ID, float volum)
    {
        for (int i = 0; i < audioDatas[ID].svNum; i++)
        {
            audioDatas[ID].pSourceVoice[i]->SetVolume(volum);

        }
    }

    //すべて開放
    void AudioManager::Release()
    {
        for (int i = 0; i < audioDatas.size(); i++)
        {
            for (int j = 0; j < audioDatas[i].svNum; j++)
            {
                audioDatas[i].pSourceVoice[j]->DestroyVoice();
            }
            delete audioDatas[i].buf.pAudioData;
            audioDatas[i].buf.pAudioData = nullptr;
        }
        audioDatas.clear();

        for (auto itr=audioDatas_.begin();itr!=audioDatas_.end();itr++)
        {
            for (int j = 0; j < itr->second.get()->svNum; j++)
            {
                itr->second.get()->pSourceVoice[j]->DestroyVoice();
            }
            delete itr->second.get()->buf.pAudioData;
            itr->second.get()->buf.pAudioData = nullptr;
        }
        audioDatas_.clear();
        CoUninitialize();
        if (pMasteringVoice)
        {
            pMasteringVoice->DestroyVoice();
        }
        pXAudio->Release();
    }
}