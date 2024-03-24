#pragma once
#include"Engine/GameObject/GameObject.h"
class ManagementPartObjectBase : public GameObject
{
protected:
	int accessUINum_;
	std::string actionName_;
public:
	ManagementPartObjectBase(Object* parent, std::string name);
	~ManagementPartObjectBase();
	int GetAccessUINumber() { return accessUINum_; }
	std::string GetActionName() { return actionName_; }
};

