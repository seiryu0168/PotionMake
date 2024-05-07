#pragma once
#include "../ItemBase.h"
class P_CP_ResourceItem : public ItemBase
{
	bool isLoaded_;
public:
	P_CP_ResourceItem(Object* parent);
	~P_CP_ResourceItem();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetModel(const std::string& modelName);
	void SetNumber(int num) { itemNum_ = num; }
	void Release() override;
};