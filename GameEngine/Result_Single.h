#pragma once
#include"Engine/GameObject/GameObject.h"
template<typename T>
class Result_Single : public GameObject
{
protected:
	T score_;
	bool isChange_;
public:
	Result_Single(Object* parent, const std::string& name)
		:GameObject(parent, name) {}
	virtual ~Result_Single() {};

};

