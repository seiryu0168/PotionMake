#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../PlayerData.h"

/// <summary>
/// ポーションを売った時のポーション情報を表示するクラス
/// </summary>
class P_MP_SettlementUI_PotionList : public GameObject
{
	XMFLOAT3 uiPos_;
	float move_;
	float scrollSpeed_;
public:
	P_MP_SettlementUI_PotionList(Object* parent);
	~P_MP_SettlementUI_PotionList();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateListUI(const std::vector<PlayerData::PotionData>& potionList);
	void Release() override;
};

