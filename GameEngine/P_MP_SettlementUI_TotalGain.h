#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_SettlementUI_TotalGain : public GameObject
{
	int totalGain_;
	std::string evaluation_;

public:
	P_MP_SettlementUI_TotalGain(Object* parent);
	~P_MP_SettlementUI_TotalGain();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetData(int totalGain,const std::string& evaluation);
	void Release() override;
};

