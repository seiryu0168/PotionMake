#pragma once
#include "../../Engine/GameObject/GameObject.h"
/// <summary>
/// ポーション管理のUI
/// </summary>
class Play_ManagementPart_PotionManagerUI : public GameObject
{
private:
public:
	Play_ManagementPart_PotionManagerUI(Object* parent);
	~Play_ManagementPart_PotionManagerUI();
	void Initialize() override;
	void Update() override;
	void CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str);
	void EnableUI();
	void InvalidUI();
	void Release() override;
};

