#pragma once
#include"Engine/GameObject/GameObject.h"
class UIBase : public GameObject
{
private:
	int UINum_;
	std::string uiName_;
public:
	UIBase(Object* parent,std::string uiName);
	~UIBase();

	int GetUINumber() { return UINum_; }
};

