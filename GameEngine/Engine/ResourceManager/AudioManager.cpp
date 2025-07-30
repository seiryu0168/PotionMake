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
    HRESULT AudioManager::Initialize()
    {
        HRESULT hr;
        //hr = CoInitializeEx(0, COINIT_MULTITHREADED);
        //if (FAILED(hr))
        //{
        //    MessageBox(NULL, L"AudioManager::Initialize 初期化に失敗しました", L"エラー", MB_OK);
        //    //return hr;
        //}
        hr = XAudio2Create(&pXAudio);
        if (FAILED(hr))
        {
            MessageBox(NULL, L"AudioManager::Initialize XAudio2の作成に失敗しました", L"エラー", MB_OK);
            return hr;
        }
        hr = pXAudio->CreateMasteringVoice(&pMasteringVoice);
        if (FAILED(hr))
        {
            MessageBox(NULL, L"AudioManager::Initialize マスタリングボイスの作成に失敗しました", L"エラー", MB_OK);
            return hr;
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
        if (hFile == INVALID_HANDLE_VALUE)
        {
            DWORD err = GetLastError();
            HRESULT hr = HRESULT_FROM_WIN32(err);
            return -1;
        }
        DWORD dwBytes = 0;
        Chunk riffChunk;
        if (ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL)==FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
       
        if (ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        char wave[4];
        if(ReadFile(hFile, &wave, 4, &dwBytes, NULL)==FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        Chunk formatChunk = { 0 };
        while (formatChunk.id[0] != 'f') {
            if (ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL) == FALSE)
                return -1;
        }
        if(ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        //フォーマットを読み取る
        //https://learn.microsoft.com/ja-jp/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
        WAVEFORMATEX fmt;
        //形式
        if (ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load 形式の読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        //チャンネル（モノラル/ステレオ）
        if(ReadFile(hFile, &fmt.nChannels,       2, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load チャンネル読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        //サンプリング数
        if(ReadFile(hFile, &fmt.nSamplesPerSec,  4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load サンプリング数読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        //1秒あたりのバイト数
        if(ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load バイト数読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        //ブロック配置
        if(ReadFile(hFile, &fmt.nBlockAlign,     2, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ブロック配置読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        //サンプル当たりのビット数
        if(ReadFile(hFile, &fmt.wBitsPerSample,  2, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ビット数読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }

        //波形データの読み込み
        Chunk data = { 0 };
        while (data.id[0] != 'd')
        {
            if (ReadFile(hFile, &data.id, 4, &dwBytes, NULL) == FALSE)
            {
                MessageBox(nullptr, L"AudioManager::Load 波形データ読み込みに失敗", L"エラー", MB_OK);
                return -1;
            }
            if (data.id[0] == 'd' || data.id[1] == 'a')
                break;
            else
            {
                //サイズ調べて
                if(ReadFile(hFile, &data.size, 4, &dwBytes, NULL)==FALSE)
                {
                    MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
                    return -1;
                }
                std::unique_ptr<char[]> pBuffer = std::make_unique<char[]>(data.size); //無駄に読み込む 
                if (ReadFile(hFile, pBuffer.get(), data.size, &dwBytes, NULL) == FALSE)
                {
                    MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
                    return -1;
                }
            }
        }
        if(ReadFile(hFile, &data.size, 4, &dwBytes, NULL)==FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
        char* pBuffer_ = new char[data.size];
        //std::unique_ptr<char[]> pBuffer;
        //pBuffer = std::make_unique<char[]>(data.size);
        //std::unique_ptr<char[]> pBuffer(new char[data.size]);
        //ReadFile(hFile, pBuffer.get(), data.size, &dwBytes, NULL);
        if (ReadFile(hFile, pBuffer_, data.size, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return -1;
        }
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
            unsigned long    size;   // サイズ
        };
        //ファイルを開く
        HANDLE hFile;
        hFile = CreateFileA(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            DWORD err = GetLastError();
            HRESULT hr = HRESULT_FROM_WIN32(err);
            return nullptr;
        }
        DWORD dwBytes = 0;
        Chunk riffChunk;
        if (ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL)==FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }

        if (ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        char wave[4];
        if (ReadFile(hFile, &wave, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        Chunk formatChunk = {0};
        while (formatChunk.id[0] != 'f') {
            if (ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL) == FALSE)
                return nullptr;
        }
        if (ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        //フォーマットを読み取る
        //https://learn.microsoft.com/ja-jp/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
        WAVEFORMATEX fmt;
        //形式
        if (ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load 形式の読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        //チャンネル（モノラル/ステレオ）
        if (ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load チャンネル読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        //サンプリング数
        if (ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load サンプリング数読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        //1秒あたりのバイト数
        if (ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load バイト数読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        //ブロック配置
        if (ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ブロック配置読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        //サンプル当たりのビット数
        if (ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ビット数読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }

        //波形データの読み込み
        Chunk data = { 0 };
        while (data.id[0] != 'd')
        {
            if (ReadFile(hFile, &data.id, 4, &dwBytes, NULL) == FALSE)
            {
                MessageBox(nullptr, L"AudioManager::Load 波形データ読み込みに失敗", L"エラー", MB_OK);
                return nullptr;
            }
            if (data.id[0] == 'd' || data.id[1] == 'a')
                break;
            else
            {
                //サイズ調べて
                if (ReadFile(hFile, &data.size, 4, &dwBytes, NULL) == FALSE)
                {
                    MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
                    return nullptr;
                }
                std::unique_ptr<char[]> pBuffer = std::make_unique<char[]>(data.size); //無駄に読み込む 
                if (ReadFile(hFile, pBuffer.get(), data.size, &dwBytes, NULL) == FALSE)
                {
                    MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
                    return nullptr;
                }
            }
        }
        if (ReadFile(hFile, &data.size, 4, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
        char* pBuffer_ = new char[data.size];
        //std::unique_ptr<char[]> pBuffer;
        //pBuffer = std::make_unique<char[]>(data.size);
        //std::unique_ptr<char[]> pBuffer(new char[data.size]);
        //ReadFile(hFile, pBuffer.get(), data.size, &dwBytes, NULL);
        if (ReadFile(hFile, pBuffer_, data.size, &dwBytes, NULL) == FALSE)
        {
            MessageBox(nullptr, L"AudioManager::Load ファイル読み込みに失敗", L"エラー", MB_OK);
            return nullptr;
        }
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
        if (ID < 0)
            return;
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
        if (ID < 0)
            return;
        for (int i = 0; i < audioDatas[ID].svNum; i++)
        {
            audioDatas[ID].pSourceVoice[i]->Stop();
            audioDatas[ID].pSourceVoice[i]->FlushSourceBuffers();
        }
    }

    void AudioManager::SetVolume(int ID, float volum)
    {
        if (ID < 0)
            return;
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
        if (pMasteringVoice)
        {
            pMasteringVoice->DestroyVoice();
        }
        pXAudio->Release();
        //CoUninitialize();
    }
}