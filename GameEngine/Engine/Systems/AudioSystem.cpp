#include "AudioSystem.h"
#include"../Coordinator.h"
#include"../GameObject/GameObject.h"
AudioSystem::AudioSystem()
{
}

void AudioSystem::CheckRemove()
{
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		if (Coordinator::GetComponent<Audio>(entity).GetAttachedObject() != nullptr && Coordinator::GetComponent<Audio>(entity).GetAttachedObject()->IsDead())
			Coordinator::RemoveComponent<Audio>(entity);
	}
}

void AudioSystem::Release()
{
	//for文内で値を消すのでコピーして回す
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::RemoveComponent<Audio>(entity);
		Coordinator::DestroyEntity(entity);
	}
}
