#pragma once
#include <string>
#include <memory>
#include <xaudio2.h>

//-----------------------------------------------------------
//�T�E���h���Ǘ�����iXAudio�g�p�j
//-----------------------------------------------------------
namespace AudioManager
{
	struct AudioData
	{
		//�T�E���h���
		XAUDIO2_BUFFER buf = {};

		//�\�[�X�{�C�X
		std::unique_ptr<IXAudio2SourceVoice* []> pSourceVoice = nullptr;

		//�����Đ��ő吔
		int svNum;

		//�t�@�C����
		std::string fileName;
	};
	//������
	HRESULT Initialize();

	//�T�E���h�t�@�C��(.wav�j�����[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName	�t�@�C����
	//�����FsvNum�@		�����ɖ炷�ő吔�i�ȗ��j
	//�ߒl�F���̃f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(const std::string& fileName,bool loopFlag=false,float volume=1.0f, int svNum = 1);
	std::shared_ptr<AudioData> Load_Component(const std::string& fileName, bool loopFlag = false, float volume = 1.0f, int svNum = 1);
	//�Đ�
	//�����Fhandle	�炵�����T�E���h�̔ԍ�
	void Play(int ID);
	void Stop(int ID);

	void SetVolume(int ID, float volum);

	//���ׂĊJ��
	void Release();
};
