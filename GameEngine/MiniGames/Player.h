#pragma once
#include "../Engine/GameObject/GameObject.h"

//プレイヤーの基底クラス
class Player : public GameObject
{
protected:
	//プレイヤーの番号
	int Playerid_;

public:
	Player(Object* parent, const std::string& name);
	virtual ~Player() {}

	void SetID(int id) { Playerid_ = id; }
	int GetID() const { return Playerid_; }
};

