#pragma once
#include "../Engine/GameObject/GameObject.h"

//�v���C���[�̊��N���X
class Player : public GameObject
{
protected:
	//�v���C���[�̔ԍ�
	int Playerid_;

public:
	Player(Object* parent, const std::string& name);
	virtual ~Player() {}

	void SetID(int id) { Playerid_ = id; }
	int GetID() const { return Playerid_; }
};

