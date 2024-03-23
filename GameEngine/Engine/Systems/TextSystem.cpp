#include "TextSystem.h"
#include"../Coordinator.h"
#include"../GameObject/GameObject.h"
TextSystem::TextSystem() : System()
{
}

void TextSystem::Draw(int layerNum)
{
	for (Entity entity : entities_)
	{
		Coordinator::GetComponent<Text>(entity).Draw(layerNum);
	}
}

void TextSystem::CheckRemove()
{
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		if (Coordinator::GetComponent<Text>(entity).GetAttachedObject()->IsDead())
			Coordinator::RemoveComponent<Text>(entity);
	}
}

void TextSystem::Release()
{
	//for文内で値を消すのでコピーして回す
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::RemoveComponent<Text>(entity);
		Coordinator::DestroyEntity(entity);
	}
}
