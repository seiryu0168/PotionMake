#include "P_CommandMemory.h"
#include "CommandMemory.h"
#include "../Engine/DirectX_11/Input.h"

P_CommandMemory::P_CommandMemory(Object* parent)
	: Player(parent, "P_CommandMemory"), memory_((CommandMemory*)parent)
{
}

P_CommandMemory::~P_CommandMemory()
{
}

void P_CommandMemory::Initialize()
{
}

void P_CommandMemory::Update()
{
	//スタートとバックボタンは対象外にする
	switch (WORD button = Input::GetPadOnlyDown(Playerid_); button)
	{
	case NULL:
	case XINPUT_GAMEPAD_START:
	case XINPUT_GAMEPAD_BACK:
		break;
	default:
		memory_->sendCommand(button, Playerid_);
		break;
	}
}

void P_CommandMemory::Release()
{
}
