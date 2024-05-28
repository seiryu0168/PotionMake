#pragma once
#include"Engine/GameObject/GameObject.h"

/// <summary>
/// �A�C�e���֌W�̊��N���X
/// </summary>
class ItemBase : public GameObject
{
protected:
	int itemNum_;
public:
	std::string itemName_;
	XMFLOAT3 imagePos_;
	ItemBase(Object* parent, std::string name);
	~ItemBase();
	int GetItemNumber() { return itemNum_; }

};

