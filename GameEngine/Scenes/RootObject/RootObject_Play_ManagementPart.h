#pragma once
#include"../../Engine/GameObject/Object.h"
class RootObject_Play_ManagementPart : public Object
{
public:
	RootObject_Play_ManagementPart();
	~RootObject_Play_ManagementPart();
	void Initialize() override;
	void Release() override;
};

