#include "SnowCone_Cup.h"
#include"SnowCone_SyrupSumple.h"
#include"SnowCone_ToppingSumple.h"
#include"../Engine/Systems/ImageSystem.h"
#include"SnowCone_Ice.h"
#include"../Easing.h"

namespace
{
	const XMFLOAT3 DEFAULT_POS[2] = { {0,180,0},{0,0,0} };
	const XMFLOAT3 STANDBY_POS[2] = { {-2100,180,0},{2100,0,0} };
	const float EASE_MAX = 1.0f;
	const float SIZE_INTERVAL = 0.398f;
}
SnowCone_Cup::SnowCone_Cup(Object* parent)
	:GameObject(parent, "SnowCone_Cup"),
	coneSize_(0),
	iceNum_(0),
	cupNum_(0),
	easingTime_(0.0f),
	baseImagePos_({ 0,0,0 }),
	isEasing_(false),
	haveCup_(true),
	state_(SNOWCONE_STATUS::SHAVE)
{
}

SnowCone_Cup::~SnowCone_Cup()
{
}


void SnowCone_Cup::Initialize()
{
	{
		Image image(1, 0);
		image.Load("Assets/Image/SnowCone_IceImage.png");
		image.SetPositionAtPixel(DEFAULT_POS[0]);
		iceNum_ = AddComponent<Image>(image);
	}
	{
		Image image(1, 0);
		image.Load("Assets/Image/SnowCone_CupImage.png");
		image.SetPositionAtPixel(DEFAULT_POS[1]);
		cupNum_ = AddComponent<Image>(image);
	}
}

void SnowCone_Cup::Update()
{
	if (isEasing_)
	{
		switch (state_)
		{
		case SnowCone_Cup::SNOWCONE_STATUS::SHAVE:
			MoveToTopping();
			break;
		case SnowCone_Cup::SNOWCONE_STATUS::STANDBY:
			MoveToGetCup();
			break;
		case SnowCone_Cup::SNOWCONE_STATUS::TOPPING:
			MoveToCustomer();
			break;
		default:
			break;
		}
	}
}
void SnowCone_Cup::MoveToTopping()
{
	GetComponent<Image>(iceNum_).SetPositionAtPixel({ 1920 * Easing::EaseInCubic(easingTime_),DEFAULT_POS[0].y,0 });
	GetComponent<Image>(cupNum_).SetPositionAtPixel({ 1920 * Easing::EaseInCubic(easingTime_),DEFAULT_POS[1].y,0 });

	if (easingTime_ >= EASE_MAX)
	{
		easingTime_ = 0.0f;
		isEasing_ = false;
		state_ = SNOWCONE_STATUS::STANDBY;
		ChangeDrawTarget(2);
		if (haveCup_ == false)
		{
			RemoveIce();
			KillMe();
		}
		return;
	}
	easingTime_ += 0.05f;
}
void SnowCone_Cup::MoveToGetCup()
{
	for (auto& imageNum : GetComponentList<Image>())
	{
		Image& img = Coordinator::GetComponent<Image>(imageNum);
		float yPos = img.GetPosition().y;
		img.SetPositionAtPixel({ 2000.0f * Easing::EaseInCubic(easingTime_) - 2000.0f,yPos,0 });
	}
	if (easingTime_ >= EASE_MAX)
	{
		easingTime_ = 0.0f;
		isEasing_ = false;
		state_ = SNOWCONE_STATUS::TOPPING;
		if (haveCup_ == false)
		{
			RemoveIce();
			KillMe();
		}

		return;
	}
	easingTime_ += 0.05f;
}
void SnowCone_Cup::MoveToCustomer()
{
	//è„Ç…ìÆÇ≠
	for (auto& imageNum : GetComponentList<Image>())
	{
		Coordinator::GetComponent<Image>(imageNum).AddPositionAtPixel({ 0,1920 * Easing::EaseInCubic(easingTime_),0 });
	}
	if (easingTime_ >= EASE_MAX)
	{
		easingTime_ = 0.0f;
		isEasing_ = false;
		state_ = SNOWCONE_STATUS::FINISH;
		if (haveCup_ == false)
		{

			RemoveIce();
			KillMe();
		}

		return;
	}
	easingTime_ += 0.05f;
}

int SnowCone_Cup::GetConeSize()
{
	return (int)(coneSize_/ SIZE_INTERVAL);
}

float SnowCone_Cup::GetConeHeight()
{
	return coneSize_;
}

void SnowCone_Cup::SetColor(const XMFLOAT4& color)
{
	((SnowCone_Ice*)FindChild("SnowCone_Ice"))->SetColor(color);
}

void SnowCone_Cup::SetTopping(int topNum)
{
	((SnowCone_Ice*)FindChild("SnowCone_Ice"))->SetTopping(0);
}

void SnowCone_Cup::SetConeSize(float size)
{
	coneSize_ += size;
	if (coneSize_ >= SIZE_INTERVAL * 2)
		coneSize_ = SIZE_INTERVAL * 2;
	GetComponent<Image>(iceNum_).SetSize({ 1,1+coneSize_,0 });
	//if(coneSize_)
}

void SnowCone_Cup::ChangeDrawTarget(int num)
{
	GetComponent<Image>(cupNum_).SetDrawTarget(num);
	GetComponent<Image>(iceNum_).SetDrawTarget(num);
	GetComponent<Image>(cupNum_).SetAlpha(0);
	GetComponent<Image>(iceNum_).SetAlpha(0);
}

void SnowCone_Cup::ToppingSetUp()
{
	GetComponent<Image>(cupNum_).SetPositionAtPixel(STANDBY_POS[1]);
	GetComponent<Image>(iceNum_).SetPositionAtPixel(STANDBY_POS[0]);
	GetComponent<Image>(cupNum_).SetAlpha(1);
	GetComponent<Image>(iceNum_).SetAlpha(1);
}

void SnowCone_Cup::Complete(int syrupNum,int toppingNum)
{
	AddComponent<Image>(((SnowCone_SyrupSumple*)FindObject("SnowCone_SyrupSumple"))->GetComponent<Image>(syrupNum));
	AddComponent<Image>(((SnowCone_ToppingSumple*)FindObject("SnowCone_ToppingSumple"))->GetComponent<Image>(toppingNum));

}

void SnowCone_Cup::RemoveIce()
{
	for (auto& imageNum : GetComponentList<Image>())
	{
		Coordinator::RemoveComponent<Image>(imageNum);
	}
}

void SnowCone_Cup::Release()
{

}
