#pragma once
#include"MenuUI.h"
class MenuUI_ReturnHome : public MenuUI
{
	int hAudio_ReturnHome_;
	int confirmImageNum_;
	int cancelImageNum_;
	bool isClickedButton_;
public:
	MenuUI_ReturnHome(Object* parent);
	~MenuUI_ReturnHome();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetDrawFlag(bool flag);
	void ClickOKButton();
	void ClickCancelButton();
	void Release() override;
};

