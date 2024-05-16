#pragma once
#include "../../Window_Base.h"
#include "../../Engine/Time.h"

/// <summary>
/// ポーションを売った時の金額を表示するクラス
/// </summary>
class P_MP_SettlementUI_TotalGain : public Window_Base
{
	int totalGain_;
	float currentGain_;
	float gainDiff_;
	float showTime_;
	int hAudio_Money_;
	int count_;
	std::string evaluation_;
	XMFLOAT3 uiPos_;
	std::shared_ptr<Time::Watch> time_;

public:
	P_MP_SettlementUI_TotalGain(Object* parent);
	~P_MP_SettlementUI_TotalGain();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetData(int totalGain,const std::string& evaluation);
	//void CreateBase();
	//void CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str);
	void Release() override;
};

