#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_ManagementPart_OutingUI : public GameObject
{
private:
public:
	Play_ManagementPart_OutingUI(Object* parent);
	~Play_ManagementPart_OutingUI();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

