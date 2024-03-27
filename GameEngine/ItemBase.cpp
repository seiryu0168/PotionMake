#include "ItemBase.h"

ItemBase::ItemBase(Object* parent, std::string name)
	:GameObject(parent,name),
	itemNum_(-1),
	itemName_(""),
	imagePos_({0,0,0})
{
}

ItemBase::~ItemBase()
{
}
