#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_PotionManagerUI_DisposeStockUI : public GameObject
{
public:
	P_MP_PotionManagerUI_DisposeStockUI(Object* parent);
	~P_MP_PotionManagerUI_DisposeStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

