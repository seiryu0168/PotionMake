#pragma once
#include"../ECS/System.h"
#include"../Components/Transform.h"


class TransformSystem : public System
{
public:
	void CheckRemove() override;
	void Release() override;

};

