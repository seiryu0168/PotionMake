#pragma once
#include"../../Engine/GameObject/GameObject.h"
class Play_ManagementPart_CraftPotModel : public GameObject
{
public:
	Play_ManagementPart_CraftPotModel(Object* parent);
	~Play_ManagementPart_CraftPotModel() {};

	void Initialize() override;
	//void Start() override;
	//void Update() override;
	void Release() override;
};

