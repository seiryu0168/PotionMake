#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_ManagementPart_CraftUI : public GameObject
{
	Play_ManagementPart_CraftUI(Object* parent);
	~Play_ManagementPart_CraftUI();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

