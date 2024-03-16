#pragma once
#include<bitset>
#include<queue>
#include<array>
#include<memory>
#include<assert.h>
using Entity = unsigned int;
const Entity MAX_ENTITIES = 5000;
using ComponentType = unsigned int;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

class ECS
{
};

