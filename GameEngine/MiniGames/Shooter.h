#pragma once
#include"../Engine/GameObject/GameObject.h"
class Shooter : public GameObject
{
	unsigned int playerNum_;
	bool aimMode_;
	XMFLOAT2 rotate_;
	XMVECTOR target_;
public:
	Shooter(Object* parent);
	~Shooter();
	void Initialize() override;
	void Update() override;
	void SetPlayerNumber(unsigned int num) { playerNum_ = num; }
	void ModeChange();
	void Reload();
	void Release() override;
};

