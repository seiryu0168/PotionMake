#pragma once
#include"Engine/GameObject/GameObject.h"
class PickupedItemDetailUI : public GameObject
{
public:
	PickupedItemDetailUI(Object* parent);
	~PickupedItemDetailUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

