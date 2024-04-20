#pragma once
#include"ItemBase.h"
class PickupedItem : public ItemBase
{
public:
	PickupedItem(Object* parent);
	~PickupedItem();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItemData(int itemNum, const std::string& itemName, int itemCount, const std::string& itemImageName,XMFLOAT3 pos);
	void Release() override;
};

