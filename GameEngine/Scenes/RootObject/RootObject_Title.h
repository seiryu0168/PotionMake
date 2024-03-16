#pragma once
#include"../../Engine/GameObject/Object.h"
class RootObject_Title : public Object
{
public:
	RootObject_Title();
	~RootObject_Title();
	void Initialize() override;
	void Release() override;
};

