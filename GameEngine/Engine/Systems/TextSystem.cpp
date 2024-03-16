#include "TextSystem.h"
#include"../Coordinator.h"
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

void TextSystem::Release()
{
	//for�����Œl�������̂ŃR�s�[���ĉ�
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::RemoveComponent<Text>(entity);
		Coordinator::DestroyEntity(entity);
	}
}
