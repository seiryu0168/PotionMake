#pragma once
#include"Player.h"
class Player_ManagementPart : public Player
{
private:
	std::string collisionObjectName_;
	int collisionUINum_;
public:
	Player_ManagementPart(Object* parent);
	~Player_ManagementPart();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
	void OnCollisionStay(GameObject* pTarget) override;
};

