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
	//���Ԃ̐ݒ�
	time_ = std::make_shared<Time::Watch>();
	time_->UnLock();
	//���f���p��
	Test_Model_ECSver model(this);
	model.Load("Assets/Model/Shooting_Bullet.fbx");
	AddComponent<Test_Model_ECSver>(model);

	//�R���C�_�[�̐ݒ�
	HitSphere colShape = { 1.0f };
	Collider collision({ 0,0,0 }, colShape);
	collision.SetAttachObject(this);
	AddComponent<Collider>(collision);

}

void Shooting_Bullet::Update()
{
	//�ʒu�̍X�V
	transform_->position_ += dir_ * 0.1f;
	//5�b��񂾂玀��
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
	//�i�i�Ɠ��������玀��
	if (target->GetTag() == "TargetGift")
	{
		KillMe();
		((Shooting*)GetParent())->ScoreUpdate(playerNum_, ((Shooting_TergetGift*)target)->GetScore());
	}
}
