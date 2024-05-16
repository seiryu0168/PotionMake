#pragma once
#include "../../Window_Base.h"
/// <summary>
/// 捨てるポーションを表示するUI
/// </summary>
class P_MP_PotionManagerUI_DisposeStockUI : public Window_Base
{
	XMFLOAT2 standPosition_;
	XMFLOAT3 uiPos_;
	std::vector<GameObject*> objects_;
public:
	P_MP_PotionManagerUI_DisposeStockUI(Object* parent);
	~P_MP_PotionManagerUI_DisposeStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	//void CreateBase();
	//void CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str);
	void AddDisposePotion(int potionNum, const std::string& name, const XMFLOAT3& potionColor);
	void SubDisposePotion(int potionNum);
	void Release() override;
};

