#pragma once
#include"Engine/GameObject/GameObject.h"
class ManagementPartObjectBase : public GameObject
{
protected:
	int accessUINum_;
public:
	ManagementPartObjectBase(Object* parent, std::string name);
	~ManagementPartObjectBase();
	int GetAccessUINumber() { return accessUINum_; }
};

