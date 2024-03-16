#include "Shooting_TergetGift.h"
#include"../Engine/ResourceManager/Audio.h"
namespace
{
	XMVECTOR KNOCKBACK_VEC = XMVectorSet(0, 0, 1, 0);
}
Shooting_TergetGift::Shooting_TergetGift(Object* parent)
	:GameObject(parent,"Shooting_TargetGift"),
	isHit_(false),
	fallSpeed_(0.0f)
{
	//�^�O�ݒ�
	SetTag("TargetGift");
}

Shooting_TergetGift::~Shooting_TergetGift()
{
}

void Shooting_TergetGift::Initialize()
{	
}

void Shooting_TergetGift::Update()
{
	//����������
	if (isHit_)
	{
		Fall();
	}
}

void Shooting_TergetGift::Fall()
{
	//�����鏈��
	transform_->position_ += KNOCKBACK_VEC + XMVectorSet(0, -fallSpeed_, 0, 0);
	fallSpeed_ += 0.1f;
	if (transform_->GetPositionY() <= 0)
		KillMe();
}

void Shooting_TergetGift::OnCollision(Object* target)
{
	//�����������̉����Ȃ炷
	Audio::Play(hAudio_CollisionSound_);
	isHit_ = true;
}


void Shooting_TergetGift::Release()
{
}
