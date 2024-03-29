#pragma once
#include"Engine/GameObject/GameObject.h"
class ResourceItemSlot : public GameObject
{
private:
	bool haveItem_;
public:
	ResourceItemSlot(Object* parent);
	~ResourceItemSlot();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItem(int itemNum);
	bool HaveItem() { return haveItem_; }
	void Release() override;
};

