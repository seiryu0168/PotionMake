#include "TransformSystem.h"
#include"../Coordinator.h"
void TransformSystem::Release()
{
	//for�����Œl�������̂ŃR�s�[���ĉ�
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::RemoveComponent<Transform>(entity);
		Coordinator::DestroyEntity(entity);
	}
}
