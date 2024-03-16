#pragma once
#include<bitset>
#include"ECS.h"
//コンポーネント配列の基底クラス
class IComponentArray
{
public:
	virtual ~IComponentArray()=default;
	virtual void EntityDestroyed(const Entity& entity) = 0;
	virtual void Clear() = 0;
};

