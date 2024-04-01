#pragma once
#include"Engine/GameObject/GameObject.h"
class ItemBase : public GameObject
{
protected:
	int itemNum_;
public:
	std::string itemName_;
	XMFLOAT3 imagePos_;
	ItemBase(Object* parent, std::string name);
	~ItemBase();

};

