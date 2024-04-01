#pragma once
#include"ItemBase.h"
/// <summary>
/// ポーション制作用の素材
/// </summary>
class ResourceItem : public ItemBase
{
private:
	bool isLoadedImage_;
	XMFLOAT3 imagePos_;
	int resourceCount_;
	GameObject* potObject_;
public:
	ResourceItem(Object* parent);
	~ResourceItem();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItemNum(int num) { itemNum_ = num; }
	int GetItemNum() { return itemNum_; }
	void LoadItem(std::string name,int resourceCount);
	bool IsLoaded() { return isLoadedImage_; }
	void Release() override;
};