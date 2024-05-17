#pragma once
#include "../../Window_Base.h"
#include "../../PlayerData.h"

/// <summary>
/// ポーションを売った時のポーション情報を表示するクラス
/// </summary>
class P_MP_SettlementUI_PotionList : public Window_Base
{
	XMFLOAT3 uiPos_;
	XMFLOAT2 potionPos_;
	float move_;
	float scrollSpeed_;
public:
	P_MP_SettlementUI_PotionList(Object* parent);
	~P_MP_SettlementUI_PotionList();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateListUI(const std::vector<PlayerData::PotionData>& potionList);
	void CreatePotionUI(int tier,const std::string& name,const XMFLOAT3& color,int price,int count);
	//void CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str);
	void Release() override;
};

