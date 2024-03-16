#include "SnowCone_ToppingSumple.h"
#include"../Easing.h"
#include"../Engine/Systems/ModelSystem.h"
#include"../Engine/Systems/ImageSystem.h"

namespace
{
	const XMFLOAT3 SYRUPPOS = { 0,180,0 };
	const XMFLOAT3 DEFAULT_POS = { 0,1200.0f,0 };
}

SnowCone_ToppingSumple::SnowCone_ToppingSumple(Object* parent)
	:GameObject(parent ,"SnowCone_ToppingSumple"),
	sumplePos_({0,0,0}),
	currentNum_(0),
	offsetPosY_(0), 
	easingTime_(1.0f),
	isMove_(false)
{
}

SnowCone_ToppingSumple::~SnowCone_ToppingSumple()
{
}

void SnowCone_ToppingSumple::Initialize()
{
	//�摜�ǂݍ���
	{
		Image image(2, 1);
		image.Load("Assets/Image/SnowCone_Topping_Adzuki.png");
		image.SetPositionAtPixel(SYRUPPOS);
		image.SetAlpha(0);
		AddComponent<Image>(image);
	}
	{
		Image image(2, 1);
		image.Load("Assets/Image/SnowCone_Topping_Blueberry.png");
		image.SetPositionAtPixel(SYRUPPOS);
		image.SetAlpha(0);
		AddComponent<Image>(image);
	}
	{
		Image image(2, 1);
		image.Load("Assets/Image/SnowCone_Topping_Raspberry.png");
		image.SetPositionAtPixel(SYRUPPOS);
		image.SetAlpha(0);
		AddComponent<Image>(image);
	}
}

void SnowCone_ToppingSumple::Update()
{
	//�g�b�s���O�����V�����J�b�v���󂯎�����瓮��
	if (isMove_)
	{
		MoveSumple((DEFAULT_POS.y*Easing::EaseLinear(easingTime_)) + offsetPosY_);
		easingTime_ -= 0.03f;
	}
}

void SnowCone_ToppingSumple::ChangeSumple(int num)
{
	//���S�������ɂ��āA�����̔ԍ��̉摜����������悤�ɂ���
	for (auto& imageNum : GetComponentList<Image>())
		Coordinator::GetComponent<Image>(imageNum).SetAlpha(0);
	
	if (num < GetComponentList<Image>().size())
	{
		GetComponent<Image>(num).SetAlpha(1);
	}
}

void SnowCone_ToppingSumple::SetSumpleSize(float size)
{
	//�����X�̃T�C�Y����g�b�s���O�̑傫�����v�Z
	size += 1.0f;
	float toppingPosition = SYRUPPOS.y + (256.0f * size) -30.0f;
	for (auto& imageNum : GetComponentList<Image>())
	{
		Coordinator::GetComponent<Image>(imageNum).SetPositionAtPixel({ 0,toppingPosition,0 });
		Coordinator::GetComponent<Image>(imageNum).SetSize({ 1 / size,1 ,0});
		Coordinator::GetComponent<Image>(imageNum).SetAlpha(0);
	}
	offsetPosY_ = toppingPosition;
}

void SnowCone_ToppingSumple::MoveSumple(float pos)
{
	//easingTime_��0�ɂȂ�܂œ�����
	sumplePos_.y = pos;
	for (auto& imageNum : GetComponentList<Image>())
	{
		Coordinator::GetComponent<Image>(imageNum).SetPositionAtPixel(sumplePos_);
	}
	if (easingTime_ <= 0)
	{
		isMove_ = false;
		easingTime_ = 1.0f;
	}
}

void SnowCone_ToppingSumple::Reset()
{
	//�e�p�����[�^�����Z�b�g
	for (auto& imageNum : GetComponentList<Image>())
	{
		Coordinator::GetComponent<Image>(imageNum).SetPositionAtPixel(DEFAULT_POS);
		Coordinator::GetComponent<Image>(imageNum).SetSize({ 1,1,0 });
		Coordinator::GetComponent<Image>(imageNum).SetAlpha(0);
	}
	isMove_ = false;
	easingTime_ = 1.0f;
	sumplePos_ = { 0,0,0 };
}

void SnowCone_ToppingSumple::Release()
{
}
