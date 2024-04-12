#pragma once
#include"Engine/GameObject/GameObject.h"
#include"Engine/Time.h"
class Title : public GameObject
{
private:
	enum class STATE
	{
		WAIT,
		PUSHED
	} State_;
	int Frame_;

	int hAudio_;

	std::unique_ptr<Time::Watch> time_;
	void Waiting();
	void Pushed();

	float timeF_;
public:
	Title(Object* parent);
	~Title();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

