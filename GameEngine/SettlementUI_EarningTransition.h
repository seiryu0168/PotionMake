#pragma once
#include"Engine/GameObject/GameObject.h"
class SettlementUI_EarningTransition : public GameObject
{

public:
	SettlementUI_EarningTransition(Object* parent);
	~SettlementUI_EarningTransition();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

