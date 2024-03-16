#include "SnowCone_ToppingMenu.h"
#include"../Engine/ResourceManager/Audio.h"
SnowCone_ToppingMenu::SnowCone_ToppingMenu(Object* parent, const std::string& name)
	:GameObject(parent,name),
	state_(SELECT_STATE::INPUT),
	selectNum_(0),
	hAudio_CursorMove_(-1),
	hAudio_PushButton_(-1)
{
	time_ = std::make_unique<Time::Watch>();
	hAudio_CursorMove_ = Audio::Load("Assets/Audio/CursorMove12.wav",false,1.0f,8);
	assert(hAudio_CursorMove_ >= 0);
	hAudio_PushButton_ = Audio::Load("Assets/Audio/PushButton44.wav",false,1.0f,8);
	assert(hAudio_PushButton_ >= 0);
}

SnowCone_ToppingMenu::~SnowCone_ToppingMenu()
{
}

void SnowCone_ToppingMenu::Initialize()
{
}

void SnowCone_ToppingMenu::Reset()
{
	selectNum_ = 0;
	state_ = SELECT_STATE::INPUT;
}


void SnowCone_ToppingMenu::Release()
{
}
