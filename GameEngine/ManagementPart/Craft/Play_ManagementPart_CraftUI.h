#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// ポーション制作を行う時のUI
/// </summary>
class Play_ManagementPart_CraftUI : public GameObject
{
	//GameObject* craftUIs[3];
public:
	Play_ManagementPart_CraftUI(Object* parent);
	~Play_ManagementPart_CraftUI();
	void Initialize() override;
	void Update() override;
	void DisplayCraftProcess(const std::vector<int>& itemNumList);
	void DisplayResult();
	void BeforeDeath() override;
	void CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str);
	void Release() override;
};

