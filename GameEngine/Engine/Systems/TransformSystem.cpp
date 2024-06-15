#include "TransformSystem.h"
#include"../Coordinator.h"
#include"../GameObject/GameObject.h"
void TransformSystem::CheckRemove()
{
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Transform& transform = Coordinator::GetComponent<Transform>(entity);
		if (transform.IsDead())
		{
			for (auto&& itr = transform.pParent_->childList_.begin(); itr != transform.pParent_->childList_.end();)
			{
				if (transform.GetAttachedObject()->GetTransformEntity() == (*itr)->GetAttachedObject()->GetTransformEntity())
				{
					itr = transform.pParent_->childList_.erase(itr);
					break;
				}
				else
					itr++;
			}
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
