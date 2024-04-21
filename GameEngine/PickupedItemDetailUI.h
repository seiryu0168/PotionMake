#pragma once
#include"Engine/GameObject/GameObject.h"
class PickupedItemDetailUI : public GameObject
{
	XMFLOAT3 uiPos_;
public:
	PickupedItemDetailUI(Object* parent);
	~PickupedItemDetailUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItemData(int itemNum);
	void Release() override;
};

