#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_CraftUI_PrepareUI : public GameObject
{
public:
	P_MP_CraftUI_PrepareUI(Object* parent);
	~P_MP_CraftUI_PrepareUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

