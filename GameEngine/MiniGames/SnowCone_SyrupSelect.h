#pragma once
#include"SnowCone_ToppingMenu.h"
class SnowCone_SyrupSelect : public SnowCone_ToppingMenu
{
private:
	int selectFrame_;
	int syrupText_;
	
public:
	SnowCone_SyrupSelect(Object* parent);
	~SnowCone_SyrupSelect();

	void Initialize() override;
	void Update() override;
	void Move();
	void Input();
	void UIReset();
	int GetSyrupNum() { return selectNum_; }
	void Release() override;
};

