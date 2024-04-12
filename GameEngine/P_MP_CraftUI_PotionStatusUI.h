#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// ポーションの各パラメータを表示するクラス
/// </summary>
class P_MP_CraftUI_PotionStatusUI : public GameObject
{
private:
	XMFLOAT2 uiPos_;
	std::vector<GameObject*> statusObjectList_;
public:
	P_MP_CraftUI_PotionStatusUI(Object* parent);
	~P_MP_CraftUI_PotionStatusUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateBase();
	void ApplicationStatusData(std::vector<float> status);
	void Release() override;
};

