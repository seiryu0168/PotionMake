#pragma once
#include"../ECS/System.h"
#include"../Components/Audio.h"
class AudioSystem : public System
{
public:
	AudioSystem();
	~AudioSystem() {};

	void CheckRemove() override;
	void Release() override;
};

