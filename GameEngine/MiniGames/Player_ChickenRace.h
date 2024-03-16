#pragma once
#include "Player.h"
#include "../Engine/Components/Particle.h"
#include "../Engine/Time.h"

class Player_ChickenRace : public Player
{
private:
	Time::Watch watch_;

	int parHand_;
	float parPos_;

	Particle* Particle_;

	int TargetTime_;

	bool CallFin_;

	//パーティクルを初期化する
	void CreateParticle();

	void CreateFireworks();

	void Finish();
public:
	Player_ChickenRace(Object* parent);
	~Player_ChickenRace() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

