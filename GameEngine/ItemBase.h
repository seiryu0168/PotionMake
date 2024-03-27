#pragma once
#include"Engine/GameObject/GameObject.h"
class ItemBase : public GameObject
{
private:
	int itemNum_;
	std::string itemName_;
public:
	XMFLOAT3 imagePos_;
	ItemBase(Object* parent, std::string name);
	~ItemBase();

};

