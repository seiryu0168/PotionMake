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
	//画像読み込み
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
	//トッピング役が新しくカップを受け取ったら動く
	if (isMove_)
	{
		MoveSumple((DEFAULT_POS.y*Easing::EaseLinear(easingTime_)) + offsetPosY_);
		easingTime_ -= 0.03f;
	}
}

void SnowCone_ToppingSumple::ChangeSumple(int num)
{
	//一回全部透明にして、引数の番号の画像だけ見えるようにする
	for (auto& imageNum : GetComponentList<Image>())
		Coordinator::GetComponent<Image>(imageNum).SetAlpha(0);
	
	if (num < GetComponentList<Image>().size())
	{
		GetComponent<Image>(num).SetAlpha(1);
	}
}

void SnowCone_ToppingSumple::SetSumpleSize(float size)
{
	//かき氷のサイズからトッピングの大きさを計算
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
	//easingTime_が0になるまで動かす
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
	//各パラメータをリセット
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
