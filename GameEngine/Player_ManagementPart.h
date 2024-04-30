#pragma once
#include"Player.h"
class Player_ManagementPart : public Player
{
private:
	std::string collisionObjectName_;
	int collisionUINum_;
	XMFLOAT2 canMoveArea_;
	int hAudio_Move_;
public:
	Player_ManagementPart(Object* parent);
	~Player_ManagementPart();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void MoveControll() override;
	void Release() override;
	void OnCollisionStay(GameObject* pTarget) override;
};

