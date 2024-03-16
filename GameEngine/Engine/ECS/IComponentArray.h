#pragma once
#include<bitset>
#include"ECS.h"
//�R���|�[�l���g�z��̊��N���X
class IComponentArray
{
public:
	virtual ~IComponentArray()=default;
	virtual void EntityDestroyed(const Entity& entity) = 0;
	virtual void Clear() = 0;
};

