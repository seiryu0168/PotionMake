#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_CraftUI_PotionStockUI : public GameObject
{
	P_MP_CraftUI_PotionStockUI(Object* parent);
	~P_MP_CraftUI_PotionStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;

};

