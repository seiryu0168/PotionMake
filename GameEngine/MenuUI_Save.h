#pragma once
#include "UIBase.h"
class MenuUI_Save : public UIBase
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

