#pragma once
#include"MenuUI.h"

/// <summary>
/// �V���̃��j���[�N���X
/// </summary>
class MenuUI_NewsPaper : public MenuUI
{
	bool isClickedButton_;
	int closeButtonNum_;
public:
	MenuUI_NewsPaper(Object* parent);
	~MenuUI_NewsPaper();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetDrawFlag(bool flag);
	void ChangeText();
	void ClickCloseButton();
	void Release() override;
};

