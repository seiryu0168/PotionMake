#include "ImageSystem.h"
#include"../Coordinator.h"
#include"../GameObject/GameObject.h"
ImageSystem::ImageSystem() : System()
{
}

void ImageSystem::Draw(int layerNum)
{
	for (Entity entity : entities_)
	{
		Image& img = Coordinator::GetComponent<Image>(entity);
		if (img.IsDraw())
			img.Draw(layerNum);
	}
}

void ImageSystem::CheckRemove()
{
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		if (Coordinator::GetComponent<Image>(entity).GetAttachedObject()!=nullptr&&Coordinator::GetComponent<Image>(entity).GetAttachedObject()->IsDead())
			Coordinator::RemoveComponent<Image>(entity);
	}
}

void ImageSystem::Release()
{
	//for文内で値を消すのでコピーして回す
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::RemoveComponent<Image>(entity);
		Coordinator::DestroyEntity(entity);
	}
}

int ImageSystem::IsHitCursorAny()
{
	for (Entity entity : entities_)
	{
		if (Coordinator::GetComponent<Image>(entity).IsHitCursor())
			return entity;
	}
	return -1;
}
