#include "RootObject_Play_CollectionPart.h"
#include "../../CollectionPart/CollectionPart_Ground.h"
#include"../../Player_CollectionPart.h"
#include"../../CollectionPart/Play_CollectionPart_StageManager.h"
#include"../../Play_UIManager.h"
#include"../../Engine/ResourceManager/AudioManager.h"
RootObject_Play_CollectionPart::RootObject_Play_CollectionPart()
	:hAudio_BGM_(-1)
{
}

RootObject_Play_CollectionPart::~RootObject_Play_CollectionPart()
{
}

void RootObject_Play_CollectionPart::Initialize()
{
	Instantiate<Player_CollectionPart>(this);
	Instantiate<Play_CollectionPart_StageManager>(this);
	Instantiate<CollectionPart_Ground>(this);
	Instantiate<Play_UIManager>(this);

	hAudio_BGM_ = AudioManager::Load("Assets/Audio/CollectionPart_BGM.wav",true);
	AudioManager::Play(hAudio_BGM_);
}

void RootObject_Play_CollectionPart::Release()
{
}
