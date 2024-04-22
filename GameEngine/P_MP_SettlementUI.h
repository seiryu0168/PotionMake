#pragma once
#include"Engine/GameObject/GameObject.h"
#include"PlayerData.h"
class P_MP_SettlementUI : public GameObject
{
	int mask_;
	std::vector<PlayerData::PotionData> potionDataList_;

public:
	P_MP_SettlementUI(Object* parent);
	~P_MP_SettlementUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateResoultUI();
	void Release() override;
};

