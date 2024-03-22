#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_ManagementPart_BaseUI : public GameObject
{
private:
public:
	Play_ManagementPart_BaseUI(Object* parent);
	~Play_ManagementPart_BaseUI();
	void Initialize() override;
	void Update() override;
	void Release() override;

};

