#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// �|�[�V����������s������UI
/// </summary>
class Play_ManagementPart_CraftUI : public GameObject
{
public:
	Play_ManagementPart_CraftUI(Object* parent);
	~Play_ManagementPart_CraftUI();
	void Initialize() override;
	void Update() override;
	void DisplayCraftProcess(const std::vector<int>& itemNumList);
	void DisplayResult();
	void Release() override;
};

