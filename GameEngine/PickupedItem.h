#pragma once
#include"ItemBase.h"
class PickupedItem : public ItemBase
{
	int itemCount_;
public:
	PickupedItem(Object* parent);
	~PickupedItem();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItemData(int itemNum, const std::string& itemName, int itemCount, const std::string& itemImageName,XMFLOAT3 pos);
	int GetItemCount() { return itemCount_; }
	void Release() override;
};

