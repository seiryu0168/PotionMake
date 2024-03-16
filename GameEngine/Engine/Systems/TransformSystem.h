#pragma once
#include"../ECS/System.h"
#include"../Components/Transform.h"


class TransformSystem : public System
{
	void Release() override;

};

