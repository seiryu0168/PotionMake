#pragma once
#include "../../Window_Base.h"

/// <summary>
/// ポーションを売った時の売上の推移を表示するクラス
/// </summary>
class SettlementUI_EarningTransition : public Window_Base
{
	XMFLOAT3 uiPos_;
	float gaugeSize_;
	std::vector<int> gainList_;
	int firstGaugeNum_;
public:
	SettlementUI_EarningTransition(Object* parent);
	~SettlementUI_EarningTransition();

	void Initialize() override;
	void Start() override;
	void Update() override;
	//void CreateBase();
	void SetData(const std::vector<int>& gainList);
	//void CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str);
	void Release() override;
};