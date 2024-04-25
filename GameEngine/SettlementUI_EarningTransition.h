#pragma once
#include"Engine/GameObject/GameObject.h"
class SettlementUI_EarningTransition : public GameObject
{
	XMFLOAT3 uiPos_;
	std::vector<int> gainList_;
	int firstGaugeNum_;
public:
	SettlementUI_EarningTransition(Object* parent);
	~SettlementUI_EarningTransition();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateBase();
	void SetData(const std::vector<int>& gainList);
	void Release() override;
};