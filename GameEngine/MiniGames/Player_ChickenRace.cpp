#include "Player_ChickenRace.h"
#include "ChickenRace.h"
#include "../Engine/DirectX_11/Input.h"
#include <format>
#include <random>


namespace
{
	static const int fwLife = 75;

	std::vector<float> fwLayer_ = {
		0.1f, 0.15f, 0.2f, 0.3f, 0.3f, 0.35f, 0.4f, 0.5f, 0.5f
	};
	std::vector<std::pair<XMFLOAT4, XMFLOAT4>> fwColor_ = {
		{{0.1f, 1, 1, 1}, {0, -1.0f / fwLife, -1.0f / fwLife, 0}},
		{{0.1f, 1, 1, 1}, {0, -1.0f / fwLife, -1.0f / fwLife, 0}},
		{{1, 0.1f, 1, 1}, {-1.0f / fwLife, 0, -1.0f / fwLife, 0}},
		{{1, 0.1f, 1, 1}, {-1.0f / fwLife, 0, -1.0f / fwLife, 0}},
		{{1, 1, 0.1f, 1}, {-1.0f / fwLife, -1.0f / fwLife, 0, 0}},
		{{1, 1, 0.1f, 1}, {-1.0f / fwLife, -1.0f / fwLife, 0, 0}},
		{{1, 1, 1, 1}, {-1.0f / fwLife, -1.0f / fwLife, 0, 0}},
		{{1, 1, 1, 1}, {-1.0f / fwLife, 0, -1.0f / fwLife, 0}},
		{{1, 1, 1, 1}, {0, -1.0f / fwLife, -1.0f / fwLife, 0}},
	};
}

Player_ChickenRace::Player_ChickenRace(Object* parent)
	: Player(parent, "Player_ChickenRace"), watch_(), TargetTime_(0), CallFin_(false), Particle_(nullptr), parHand_(-1), parPos_(0)
{
}

void Player_ChickenRace::Initialize()
{
	parPos_ = -15 + Playerid_ * 30;

	watch_.UnLock();
	CreateParticle();
}

void Player_ChickenRace::Update()
{
	if (!CallFin_)
	{
		float f = watch_.GetSeconds<float>();

		if (Input::GetPadOnlyDown(Playerid_) && f > 1)
		{
			CreateFireworks();
			Finish();
			return;

		}

		//1秒かけて時間を見えなくする
		if (f >= 4 && Particle_->GetEmitter(parHand_)->data.color.w != 0)
		{
			Particle_->GetEmitter(parHand_)->data.color.w = (float)std::lerp(1, 0, f - 4);
		}
	}
}

void Player_ChickenRace::Draw()
{
}

void Player_ChickenRace::Release()
{
}

void Player_ChickenRace::CreateParticle()
{
	//火花
	Particle particle(this, 1);
	EmitterData data;
	data.position = XMFLOAT3(parPos_, 0.05f, 0);
	data.delay = 10;
	data.number = 2;
	data.lifeTime = 20;
	data.dir = XMFLOAT3(0, -1, 0);
	data.dirErr = XMFLOAT3(5, 150, 0);
	data.gravity = 0.001f;
	data.speedErr = 0.8f;
	data.size = XMFLOAT2(0.4f, 0.4f);
	data.sizeErr = XMFLOAT2(0.4f, 0.4f);
	data.scale = XMFLOAT2(1, 1);
	data.color = XMFLOAT4(1, 1, 0.1f, 1);
	data.deltaColor = XMFLOAT4(0, -1.0f / 20, 0, -1.0f / 20);
	data.textureFileName = "Assets\\Image\\Cloud.png";
	data.firstSpeed = 0.1f;
	data.blendMode = BLEND_MODE::BLEND_ADD;
	//設定したパーティクルデータの番号を取得
	parHand_ = particle.SetData(data);
	int i = AddComponent<Particle>(particle);
	Particle_ = &GetComponent<Particle>(i);
	
}

void Player_ChickenRace::CreateFireworks()
{
	Particle_->GetEmitter(parHand_)->data.color.w = 0;

	Particle particle(this, 1);
	EmitterData data;
	data.textureFileName = "Assets\\Image\\Cloud.png";
	data.position = XMFLOAT3(parPos_, 0.05f, 0);
	data.delay = 0;
	data.number = 50;
	data.lifeTime = fwLife;
	data.dir = XMFLOAT3(0, 1, 0);
	data.dirErr = XMFLOAT3(90, 90, 160);
	data.gravity = 0.01f;
	data.speedErr = -0.01f;
	data.size = XMFLOAT2(0.3f, 0.3f);
	data.sizeErr = XMFLOAT2(0.2f, 0.2f);
	data.scale = XMFLOAT2(1.01f, 1.01f);

	//シャッフル
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(fwLayer_.begin(), fwLayer_.end(), engine);
	std::shuffle(fwColor_.begin(), fwColor_.end(), engine);

	for (int i = 0; i < fwLayer_.size(); i++)
	{
		data.color = fwColor_[i].first;
		data.deltaColor = fwColor_[i].second;
		data.firstSpeed = fwLayer_[i];
		particle.SetData(data);
		AddComponent<Particle>(particle);
	}

}

void Player_ChickenRace::Finish()
{
	watch_.Lock();
	ChickenRace* c = (ChickenRace*)GetParent();
	c->SendTime(this, watch_.GetSeconds<float>());
	RemoveComponent<Particle>();
	CallFin_ = true;
}