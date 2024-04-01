#pragma once
#include"ItemBase.h"
class ResourceItemSlot : public ItemBase
{
private:
	bool haveResource_;
	int resourceCount_;
public:
	ResourceItemSlot(Object* parent);
	~ResourceItemSlot();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItem(std::string imageName,int itemNum);
	void ItemEmpty();
	bool HaveItem() { return haveResource_; }
	void Release() override;
};

