#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// �|�[�V�����Ǘ���UI
/// </summary>
class Play_ManagementPart_PotionManagerUI : public GameObject
{
private:
public:
	Play_ManagementPart_PotionManagerUI(Object* parent);
	~Play_ManagementPart_PotionManagerUI();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

