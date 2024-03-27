#pragma once
#include"../../Engine/GameObject/Object.h"
class RootObject_Play_CollectionPart : public Object
{
public:
	RootObject_Play_CollectionPart();
	~RootObject_Play_CollectionPart();
	void Initialize() override;
	void Release() override;
};

