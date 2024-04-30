#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// UI‚ð•Â‚¶‚éƒ{ƒ^ƒ“
/// </summary>
class CloseButton : public GameObject
{
	int hAudio_Close_;
public:
	CloseButton(Object* parent);
	~CloseButton();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

