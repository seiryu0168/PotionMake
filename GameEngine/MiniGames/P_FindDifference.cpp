#include "P_FindDifference.h"
#include "FindDifference.h"
#include "../Engine/DirectX_11/Input.h"
#include <map>

namespace
{
	const std::map<WORD, CHOICES> datas =
	{
		{XINPUT_GAMEPAD_A, CHOICES::UNDER},
		{XINPUT_GAMEPAD_B, CHOICES::RIGHT},
		{XINPUT_GAMEPAD_X, CHOICES::LEFT},
		{XINPUT_GAMEPAD_Y, CHOICES::RIGHT}
	};
}

P_FindDifference::P_FindDifference(Object* parent)
	: Player(parent, "P_FindDifference"), pFD_((FindDifference*)parent)
{
}

P_FindDifference::~P_FindDifference()
{
}

void P_FindDifference::Initialize()
{
}

void P_FindDifference::Update()
{
	switch (WORD i = Input::GetPadOnlyDown(Playerid_); i)
	{
	case XINPUT_GAMEPAD_A:
	case XINPUT_GAMEPAD_B:
	case XINPUT_GAMEPAD_X:
	case XINPUT_GAMEPAD_Y:
		pFD_->SendData(datas.at(i), Playerid_);
		break;
	default:
		break;
	}
	/*if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		pFD_->SendData(datas.at(XINPUT_GAMEPAD_A), Playerid_);
	}
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		pFD_->SendData(datas.at(XINPUT_GAMEPAD_B), Playerid_);
	}
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		pFD_->SendData(datas.at(XINPUT_GAMEPAD_X), Playerid_);
	}
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y))
	{
		pFD_->SendData(datas.at(XINPUT_GAMEPAD_Y), Playerid_);
	}*/
}

void P_FindDifference::Release()
{
}
