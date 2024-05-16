#pragma once
#include "../../Window_Base.h"
/// <summary>
/// 売るポーションを表示するUI
/// </summary>
class P_MP_PotionManagerUI_SellStockUI : public Window_Base
{
	XMFLOAT2 standPosition_;
	XMFLOAT3 uiPos_;
	std::vector<GameObject*> objects_;
public:
	P_MP_PotionManagerUI_SellStockUI(Object* parent);
	~P_MP_PotionManagerUI_SellStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	//void CreateBase();
	//void CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str);
	void AddSellPotion(int potionNum, const std::string& name, const XMFLOAT3& potionColor);
	void SubSellPotion(int potionNum);
	void Release() override;
};

