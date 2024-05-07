#pragma once
#include "../ItemBase.h"
class PickupedItem : public ItemBase
{
	int itemCount_;
	bool canSelect_;
public:
	PickupedItem(Object* parent);
	~PickupedItem();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItemData(int itemNum, const std::string& itemName, int itemCount, const std::string& itemImageName,XMFLOAT3 pos);
	int GetItemCount() { return itemCount_; }
	void SetCanSelect(bool flag) { canSelect_ = flag; }
	void Release() override;
};

