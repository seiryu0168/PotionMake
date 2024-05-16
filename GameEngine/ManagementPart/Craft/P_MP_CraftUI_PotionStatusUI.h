#pragma once
#include "../../Window_Base.h"
/// <summary>
/// ポーションの各パラメータを表示するクラス
/// </summary>
class P_MP_CraftUI_PotionStatusUI : public Window_Base
{
private:
	//XMFLOAT2 uiPos_;
	std::vector<GameObject*> statusObjectList_;
public:
	P_MP_CraftUI_PotionStatusUI(Object* parent);
	~P_MP_CraftUI_PotionStatusUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	//void CreateBase();
	void SetStatusData(std::vector<float> status,const std::string& coststr);
	void Release() override;
};

