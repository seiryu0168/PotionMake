#pragma once
#include"MenuUI.h"

/// <summary>
/// �A�C�e���̃��j���[�N���X
/// </summary>
class MenuUI_Item : public MenuUI
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

