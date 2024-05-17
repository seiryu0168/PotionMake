#pragma once
#include"MenuUI.h"
class MenuUI_Status : public MenuUI
{
	int statusImageNum_;
;	int nameTextNum_;
	int moneyTextNum_;
	
	bool isClickedButton_;
	GameObject* status_;
public:
	MenuUI_Status(Object* parent);
	~MenuUI_Status();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateStatus();
	void RemoveStatus();
	void CloseStatusUI();
	void Release() override;
};

