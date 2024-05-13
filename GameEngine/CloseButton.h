#pragma once
#include "Engine/GameObject/GameObject.h"
#include<Functional>
/// <summary>
/// UI‚ð•Â‚¶‚éƒ{ƒ^ƒ“
/// </summary>
class CloseButton : public GameObject
{
	int hAudio_Close_;
	std::function<void()> clickedFunction_;
	bool isSetFunction_;
public:
	CloseButton(Object* parent);
	~CloseButton();
	void Initialize() override;
	void Start() override;
	void Update() override;
	std::function<void()>& GetFunction() { isSetFunction_ = true; return clickedFunction_; }
	void Release() override;
};

