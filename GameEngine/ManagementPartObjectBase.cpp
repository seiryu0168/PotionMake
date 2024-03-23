#include "ManagementPartObjectBase.h"

ManagementPartObjectBase::ManagementPartObjectBase(Object* parent, std::string name)
	:GameObject(parent,name),accessUINum_(-1)
{
}

ManagementPartObjectBase::~ManagementPartObjectBase()
{
}
