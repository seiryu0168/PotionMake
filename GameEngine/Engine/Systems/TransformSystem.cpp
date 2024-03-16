#include "TransformSystem.h"
#include"../Coordinator.h"
void TransformSystem::Release()
{
	//for文内で値を消すのでコピーして回す
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::RemoveComponent<Transform>(entity);
		Coordinator::DestroyEntity(entity);
	}
}
