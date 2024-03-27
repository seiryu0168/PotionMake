#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_CraftUI_ResourceStockUI : public GameObject
{
public:
	XMFLOAT3 uiPos_;
	P_MP_CraftUI_ResourceStockUI(Object* parent);
	~P_MP_CraftUI_ResourceStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};