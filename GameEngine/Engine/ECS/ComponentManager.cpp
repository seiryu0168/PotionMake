#include "ComponentManager.h"

void ComponentManager::AllRemoveComponent()
{
	componentArrays_.clear();
	componentTypes_.clear();
	nextComponentType_ = 0;
}