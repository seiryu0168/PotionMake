#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_PotionManagerUI_SellStockUI : public GameObject
{
public:
	P_MP_PotionManagerUI_SellStockUI(Object* parent);
	~P_MP_PotionManagerUI_SellStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

