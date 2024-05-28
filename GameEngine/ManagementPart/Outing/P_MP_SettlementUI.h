#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../PlayerData.h"

/// <summary>
/// ƒ|[ƒVƒ‡ƒ“”Ì”„‚ÌUI
/// </summary>
class P_MP_SettlementUI : public GameObject
{
	int mask_;
	float time_;
	bool isClose_;
	std::vector<PlayerData::PotionData> potionDataList_;
	int fadeImageNum_;
	int okImageNum_;
	int hAdio_OK_;
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

