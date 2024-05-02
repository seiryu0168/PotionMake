#pragma once
#include"Engine/GameObject/GameObject.h"
#include"PlayerData.h"
class P_MP_SettlementUI : public GameObject
{
	int mask_;
	float time_;
	std::vector<PlayerData::PotionData> potionDataList_;
	int fadeImageNum_;
public:
	P_MP_SettlementUI(Object* parent);
	~P_MP_SettlementUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateResoultUI();
	int CalcSellCount(int newsNum,int topStatus);
	void Release() override;
};

