#pragma once
#include"../Engine/GameObject/GameObject.h"
class Shooting_Gun : public GameObject
{
	unsigned short playerNum_;
	XMVECTOR frontVec_;
	int bulletCount_;
	int hAudio_Shot_;
	size_t textNum_;
public:
	Shooting_Gun(Object* parent);
	~Shooting_Gun();
	void Initialize() override;
	void Update() override;
	//�e����
	void Shot(const XMVECTOR& dir);
	//�e�𔭎˂���ʒu�擾
	XMVECTOR GetShotPos();
	//�`�悷�邩�ǂ����ݒ�
	void SetDraw(bool isDraw);
	//�c�e���擾
	int& GetBulletCount() { return bulletCount_; }
	//�����������擾
	int GetShotCount();
	//�����[�h
	void Reload();
	//�v���C���[�ԍ��ݒ�
	void SetPlayerNum_(const unsigned short& num) { playerNum_ = num; }
	void Release() override;
};

