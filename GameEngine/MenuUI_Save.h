#pragma once
#include "MenuUI.h"

/// <summary>
/// セーブのメニュークラス
/// </summary>
class MenuUI_Save : public MenuUI
{
private:
	int confirmImageNum_;
	int cancelImageNum_;
	bool isClickedButton_;
public:
	MenuUI_Save(Object* parent);
	~MenuUI_Save();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void DataSave();
	void SetDrawFlag(bool flag);
	void ClickOKButton();
	void ClickCancelButton();
	void Release() override;
};

