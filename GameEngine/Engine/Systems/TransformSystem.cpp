#include "TransformSystem.h"
#include"../Coordinator.h"
void TransformSystem::CheckRemove()
{
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		if (Coordinator::GetComponent<Transform>(entity).IsDead())
		{
			Coordinator::RemoveComponent<Transform>(entity);
			Coordinator::DestroyEntity(entity);
		}
	}
}
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
