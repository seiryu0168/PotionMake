#pragma once
#include"../UIBase.h"

class P_CP_MenuUI : public UIBase
{
	bool isReturnHome_;
	int returnImageNum_;
	int fadeImageNum_;
	int hAudio_ReturnHome_;
	float time_;
public:
	P_CP_MenuUI(Object* parent);
	~P_CP_MenuUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SaveItemData();
	void Release() override;
};

