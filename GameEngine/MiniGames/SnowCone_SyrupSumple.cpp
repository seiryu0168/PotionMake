#include "SnowCone_SyrupSumple.h"
#include"../Engine/Systems/ModelSystem.h"
#include"../Easing.h"
#include"../Engine/Systems/ImageSystem.h"
namespace
{
	const XMFLOAT3 SYRUPPOS = { 0,180, 0 };
	const XMFLOAT3 DEFAULT_POS = { 0,1200,0 };
}

SnowCone_SyrupSumple::SnowCone_SyrupSumple(Object* parent)
	:GameObject(parent,"SnowCone_SyrupSumple"),
	currentNum_(0),
	sumplePos_({0,0,0}),
	easingTime_(1.0f),
	offsetPosY_(180.0f),
	isMove_(false)
{
}

SnowCone_SyrupSumple::~SnowCone_SyrupSumple()
{
}

void SnowCone_SyrupSumple::Initialize()
{
	//画像読み込み
	{
		Image image(2, 1);
		image.Load("Assets/Image/SnowCone_Syrup_RedImage.png");
		image.SetPositionAtPixel(DEFAULT_POS);
		image.SetAlpha(0);
		AddComponent<Image>(image);
	}
	{
		Image image(2, 1);
		image.Load("Assets/Image/SnowCone_Syrup_BlueImage.png");
		image.SetPositionAtPixel(DEFAULT_POS);
		image.SetAlpha(0);
		AddComponent<Image>(image);
	}
	{
		Image image(2, 1);
		image.Load("Assets/Image/SnowCone_Syrup_GreenImage.png");
		image.SetPositionAtPixel(DEFAULT_POS);
		image.SetAlpha(0);
		AddComponent<Image>(image);
	}
}

void SnowCone_SyrupSumple::Update()
{
	//トッピング役が新しくカップを受け取ったら動く
	if (isMove_)
	{
		MoveSumple((DEFAULT_POS.y * Easing::EaseLinear(easingTime_)) + offsetPosY_);
		easingTime_ -= 0.03f;
	}
}

void SnowCone_SyrupSumple::ChangeSumple(int num)
{
	//一回全部透明にして、引数の番号だけ見えるようにする
	for (auto& imageNum : GetComponentList<Image>())
		Coordinator::GetComponent<Image>(imageNum).SetAlpha(0);

	if (num < GetComponentList<Image>().size())
	{
		GetComponent<Image>(num).SetAlpha(1);
		currentNum_ = num;
	}
}

void SnowCone_SyrupSumple::SetSyrupSize(float size)
{
	//かき氷の大きさに合わせて大きくする
	for (auto& imageNum : GetComponentList<Image>())
		Coordinator::GetComponent<Image>(imageNum).SetSize({ 1,1+size,0 });
}

void SnowCone_SyrupSumple::MoveSumple(float yPos)
{
	//イージング関数を使って動かす(easing_が0になったら止める)
	sumplePos_.y = yPos;	
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

void SnowCone_SyrupSumple::Reset()
{
	//パラメータをリセット
	for (auto& imageNum : GetComponentList<Image>())
	{
		Coordinator::GetComponent<Image>(imageNum).SetSize({ 1,1,0 });
		Coordinator::GetComponent<Image>(imageNum).SetAlpha(0);
	}
	isMove_ = false;
	easingTime_ = 1.0f;
	sumplePos_ = { 0,0,0 };
}

void SnowCone_SyrupSumple::Release()
{
}
