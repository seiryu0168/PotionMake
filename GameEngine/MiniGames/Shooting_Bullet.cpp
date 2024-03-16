#include "Shooting_Bullet.h"
#include"../Engine/Systems/ModelSystem.h"
#include"../Engine/Systems/LineParticleSystem.h"
#include"../Engine/Systems/ColliderSystem.h"
#include"../Engine/Time.h"
#include"Shooting.h"
#include"Shooting_TergetGift.h"
Shooting_Bullet::Shooting_Bullet(Object* parent)
	:GameObject(parent,"Shooting_Bullet"),dir_(XMVectorZero()), playerNum_(0)
{
}

Shooting_Bullet::~Shooting_Bullet()
{
}

void Shooting_Bullet::Initialize()
{
	//時間の設定
	time_ = std::make_shared<Time::Watch>();
	time_->UnLock();
	//モデル用意
	Test_Model_ECSver model(this);
	model.Load("Assets/Model/Shooting_Bullet.fbx");
	AddComponent<Test_Model_ECSver>(model);

	//コライダーの設定
	HitSphere colShape = { 1.0f };
	Collider collision({ 0,0,0 }, colShape);
	collision.SetAttachObject(this);
	AddComponent<Collider>(collision);

}

void Shooting_Bullet::Update()
{
	//位置の更新
	transform_->position_ += dir_ * 0.1f;
	//5秒飛んだら死ぬ
	if ( time_->GetSeconds<float>() >= 5.0f)
	{
		KillMe();
	}
}

void Shooting_Bullet::Release()
{
}

void Shooting_Bullet::OnCollision(Object* target)
{
	//景品と当たったら死ぬ
	if (target->GetTag() == "TargetGift")
	{
		KillMe();
		((Shooting*)GetParent())->ScoreUpdate(playerNum_, ((Shooting_TergetGift*)target)->GetScore());
	}
}
