#pragma once
#include"../Engine/GameObject/GameObject.h"
#include"../Engine/Time.h"
class Shooting_Bullet: public GameObject
{
	XMVECTOR dir_;
	unsigned short playerNum_;

	std::shared_ptr<Time::Watch> time_;
public:
	Shooting_Bullet(Object* parent);
	~Shooting_Bullet();
	void Initialize() override;
	void Update() override;
	//��ԕ����̐ݒ�
	void SetDir(XMVECTOR dir) { dir_ = dir; }
	void Release() override;
	//�ǂ̃v���C���[����΂������̐ݒ�
	void SetPlayerNum(const unsigned short& num) { playerNum_ = num; }
	void OnCollision(Object* target) override;
};

