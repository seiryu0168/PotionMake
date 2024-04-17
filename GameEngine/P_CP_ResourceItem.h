#pragma once
#include"ItemBase.h"
class P_CP_ResourceItem : public ItemBase
{
public:
	P_CP_ResourceItem(Object* parent);
	~P_CP_ResourceItem();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetModel(const std::string& modelName);
	void Release() override;
};