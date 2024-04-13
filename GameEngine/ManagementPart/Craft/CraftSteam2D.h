#pragma once
#include"../../Engine/GameObject/GameObject.h"
#include<random>

/// <summary>
/// ポーション制作アニメーションの湯気
/// </summary>
class CraftSteam2D : public GameObject
{
	struct SteamParticleData
	{
		int imageNum_;
		float lifeTime_;

		XMFLOAT2 firstPosition_;
		XMFLOAT2 position_;
		XMFLOAT2 velocity_;
		XMFLOAT2 size_;
		XMFLOAT4 color_;
		SteamParticleData()
		{
			imageNum_ = -1;
			lifeTime_ = 0;
			firstPosition_ = { 0,0 };
			position_ = { 0,0 };
			velocity_ = { 0,0 };
			size_ = { 0,0 };
			color_ = { 0,0,0,0 };
		}

		SteamParticleData(int num,float lifeTime,XMFLOAT2 pos,XMFLOAT2 velocity,XMFLOAT2 size,XMFLOAT4 color)
		{
			imageNum_ = num;
			lifeTime_ = lifeTime;
			position_ = pos;
			velocity_ = velocity;
			size_ = size;
			color_ = color;
		}
	};
	std::random_device rnd;
	std::mt19937 mt;
	std::uniform_real_distribution<float> randomFloatGenerator_;

	XMFLOAT2 emitterPosition_;
	XMFLOAT2 posDifferenceLimit_;
	std::vector<SteamParticleData> smokeParticle_;
	int particleCountLimit_;
	int particleCount_;
	float particleLifeTime_;
	float prevTime_;
	float interval_;
	float timeLimit_;
	float time_;
	bool isPlay_;
public:
	CraftSteam2D(Object* parent);
	~CraftSteam2D();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void PlaySmoke() { isPlay_ = true; }
	void SetSmokeParameter(float time, float delay, int smokeCount, float interval,float particleLifeTime,XMFLOAT2 positionDifferenceLimit);
	void Release() override;
};

