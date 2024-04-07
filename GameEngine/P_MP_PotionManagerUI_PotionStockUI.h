#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// É|Å[ÉVÉáÉìÇÃç›å…UI
/// </summary>
class P_MP_PotionManagerUI_PotionStockUI : public GameObject
{
	std::vector<GameObject* > potionList_;
public:
	XMFLOAT2 potionImageBasePos_;
	P_MP_PotionManagerUI_PotionStockUI(Object* parent);
	~P_MP_PotionManagerUI_PotionStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void InputPotionData();
	void CreatePotionMenu(int potionNum, const std::string& name, const XMFLOAT3& color);
	void SetEnablePotionStock(bool isEnable);
	void Release() override;

};

