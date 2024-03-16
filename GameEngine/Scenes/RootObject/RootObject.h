#pragma once
#include"../../Engine/GameObject/Object.h"

class RootObject : public Object
{
public:
	RootObject();
	~RootObject();
	void Initialize() override;
	void Release() override;
};

