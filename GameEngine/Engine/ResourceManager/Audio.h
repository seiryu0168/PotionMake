#pragma once
#include <string>

//-----------------------------------------------------------
//�T�E���h���Ǘ�����iXAudio�g�p�j
//-----------------------------------------------------------
namespace Audio
{
	//������
	void Initialize();

	//�T�E���h�t�@�C��(.wav�j�����[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName	�t�@�C����
	//�����FsvNum�@		�����ɖ炷�ő吔�i�ȗ��j
	//�ߒl�F���̃f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(const std::string& fileName,bool loopFlg=false,float volume=1.0f, int svNum = 1);

	//�Đ�
	//�����Fhandle	�炵�����T�E���h�̔ԍ�
	void Play(int ID);
	void Stop(int ID);

	void SetVolume(int ID, float volum);

	//���ׂĊJ��
	void Release();
};
