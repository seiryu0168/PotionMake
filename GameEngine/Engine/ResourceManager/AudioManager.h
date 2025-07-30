#pragma once
#include <string>
#include <memory>
#include <xaudio2.h>

//-----------------------------------------------------------
//サウンドを管理する（XAudio使用）
//-----------------------------------------------------------
namespace AudioManager
{
	struct AudioData
	{
		//サウンド情報
		XAUDIO2_BUFFER buf = {};

		//ソースボイス
		std::unique_ptr<IXAudio2SourceVoice* []> pSourceVoice = nullptr;

		//同時再生最大数
		int svNum;

		//ファイル名
		std::string fileName;
	};
	//初期化
	HRESULT Initialize();

	//サウンドファイル(.wav）をロード
	//すでに同じ名前のファイルをロード済みの場合は、既存のデータの番号を返す
	//引数：fileName	ファイル名
	//引数：svNum　		同時に鳴らす最大数（省略可）
	//戻値：そのデータに割り当てられた番号
	int Load(const std::string& fileName,bool loopFlag=false,float volume=1.0f, int svNum = 1);
	std::shared_ptr<AudioData> Load_Component(const std::string& fileName, bool loopFlag = false, float volume = 1.0f, int svNum = 1);
	//再生
	//引数：handle	鳴らしたいサウンドの番号
	void Play(int ID);
	void Stop(int ID);

	void SetVolume(int ID, float volum);

	//すべて開放
	void Release();
};
