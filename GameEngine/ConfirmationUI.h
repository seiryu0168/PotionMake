#pragma once
#include"Engine/GameObject/GameObject.h"
#include<Functional>

/// <summary>
/// Šm”FUI
/// </summary>
class ConfirmationUI : public GameObject
{
	int confirmImageNum_;
	int cancelImageNum_;
	bool isSetConfirmFunction_;
	bool isSetCancelFunction_;
	std::function<void()> confirmFunction_;
	std::function<void()> cancelFunction_;

public:
	ConfirmationUI(Object* parent);
	~ConfirmationUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetConfitmentText(const std::string& str);
	std::function<void()>& GetConfirmFunction();
	std::function<void()>& GetCancelFunction();
	void Release() override;
};

