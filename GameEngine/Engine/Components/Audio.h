#pragma once
#include"../ResourceManager/AudioManager.h"

class GameObject;
class Audio
{
private:
	std::shared_ptr<AudioManager::AudioData> audioData_;
	GameObject* attachObject_;
	std::string audioName_;
	float volume_;
public:
	Audio();
	Audio(GameObject* object);
	Audio(const std::string& fileName);
	~Audio();

	bool Load(const std::string& fileName,bool loopFlag = false, float volume = 1.0f, int svNum = 1);
	void Play();
	void Stop();
	//void 
	
	GameObject* GetAttachedObject() { return attachObject_; }
};

