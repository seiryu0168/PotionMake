#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// É|Å[ÉVÉáÉìÇÃç›å…UI
/// </summary>
class P_MP_PotionManagerUI_PotionStockUI : public GameObject
{
public:
	P_MP_PotionManagerUI_PotionStockUI(Object* parent);
	~P_MP_PotionManagerUI_PotionStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;

};

