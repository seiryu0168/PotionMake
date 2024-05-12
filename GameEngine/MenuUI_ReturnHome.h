#pragma once
#include"UIBase.h"
class MenuUI_ReturnHome : public UIBase
{
public:
	MenuUI_ReturnHome(Object* parent);
	~MenuUI_ReturnHome();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetDrawFlag(bool flag);
	void Release() override;
};

