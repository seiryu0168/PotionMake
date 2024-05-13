#pragma once
#include"UIBase.h"
class MenuUI_Item : public UIBase
{
	bool isClickedButton_;
public:
	MenuUI_Item(Object* parent);
	~MenuUI_Item();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CretateItemList();
	void ClickCloseButton();
	void Release() override;
};

