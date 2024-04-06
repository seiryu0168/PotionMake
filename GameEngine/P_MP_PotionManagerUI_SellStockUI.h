#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// 売るポーションを表示するUI
/// </summary>
class P_MP_PotionManagerUI_SellStockUI : public GameObject
{
	XMFLOAT2 standPosition_;
	std::vector<GameObject*> objects_;
public:
	P_MP_PotionManagerUI_SellStockUI(Object* parent);
	~P_MP_PotionManagerUI_SellStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void AddSellPotion(int potionNum, const std::string& name, const XMFLOAT3& potionColor);
	void SubSellPotion(int potionNum);
	void Release() override;
};

