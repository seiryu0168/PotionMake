#pragma once
#include"../../ItemBase.h"

/// <summary>
/// ëfçﬁÇì¸ÇÍÇÈòg
/// </summary>
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
	void SetItem(const std::string& resourceName,const std::string& imageName,int itemNum);
	void ItemEmpty();
	void AddCount(int increase);
	void SubCount(int subtract);
	int GetCount() { return resourceCount_; }
	bool HaveItem() { return haveResource_; }
	void Release() override;
};

