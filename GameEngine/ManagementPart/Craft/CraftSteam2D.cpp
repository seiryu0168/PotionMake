#include "CraftSteam2D.h"
#include "../../Engine/Systems/ImageSystem.h"
CraftSteam2D::CraftSteam2D(Object* parent)
	:GameObject(parent,"CraftSteam2D"),
	emitterPosition_({0,0}),
	time_(0),
	particleCount_(0),
	isPlay_(false),
	prevTime_(0)
{
}

CraftSteam2D::~CraftSteam2D()
{
}

void CraftSteam2D::Initialize()
{
	mt.seed(rnd());
}

void CraftSteam2D::Start()
{
}

void CraftSteam2D::Update()
{
	//プレイ状態なら
	if (isPlay_)
	{
		time_ += 0.016f;
		if (time_ >= timeLimit_)
		{
			isPlay_ = false;
			time_ = 0;
			return;
		}
		//一定時間ごとにパーティクルを出す
		if ((particleCount_ < particleCountLimit_)&&time_-prevTime_>=interval_)
		{

			XMFLOAT2 firstPos = { emitterPosition_.x + randomFloatGenerator_(mt),0 };
			Image steamImage(this);
			steamImage.Load("Assets/Image/SmokeImage00.png");
			steamImage.SetLayer(1);
			steamImage.SetPosition({ firstPos.x,firstPos.y,0 });
			int imageNum = AddComponent<Image>(steamImage);
			SteamParticleData data(imageNum, particleLifeTime_, firstPos, { 0,0.01f }, { 1,1 }, { 1,1,1,1 });
			data.firstPosition_ = firstPos;
			smokeParticle_.push_back(data);
			prevTime_ = time_;
		}
		//パーティクルを動かす
		for (SteamParticleData& steam : smokeParticle_)
		{
			steam.position_.x += steam.velocity_.x;
			steam.position_.y += steam.velocity_.y;
			steam.color_.w -= 0.02f;
			GetComponent<Image>(steam.imageNum_).SetPosition({ steam.position_.x ,steam.position_.y,0 });
			GetComponent<Image>(steam.imageNum_).SetAlpha(steam.color_.w);
		}
	}
}

void CraftSteam2D::SetSmokeParameter(float time, float delay, int smokeCount, float interval, float particleLifeTime, XMFLOAT2 positionDifferenceLimit)
{
	//パーティクルの各種パラメータを設定
	interval_ = interval;
	particleCountLimit_ = smokeCount;
	particleLifeTime_ = particleLifeTime;
	posDifferenceLimit_ = positionDifferenceLimit;
	timeLimit_ = time;
	std::uniform_real_distribution<float>::param_type param(positionDifferenceLimit.x, positionDifferenceLimit.y);
	randomFloatGenerator_.param(param);
}

void CraftSteam2D::Release()
{
}
