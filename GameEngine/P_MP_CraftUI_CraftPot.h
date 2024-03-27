#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_CraftUI_CraftPot : public GameObject
{
private:
		
public:
	P_MP_CraftUI_CraftPot(Object* parent);
	~P_MP_CraftUI_CraftPot();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

