#pragma once
#include"ItemBase.h"
class ResourceItem : public ItemBase
{
	XMFLOAT3 imagePos_;
public:
	ResourceItem(Object* parent);
	~ResourceItem();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};