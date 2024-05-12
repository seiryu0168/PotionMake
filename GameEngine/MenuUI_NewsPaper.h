#pragma once
#include"UIBase.h"
class MenuUI_NewsPaper : public UIBase
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
	void Release() override;
};

