#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_CraftUI_PotionStatusUI : public GameObject
{
public:
	P_MP_CraftUI_PotionStatusUI(Object* parent);
	~P_MP_CraftUI_PotionStatusUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

