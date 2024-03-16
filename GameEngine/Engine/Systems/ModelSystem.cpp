#include "ModelSystem.h"
ModelSystem::ModelSystem() : System()
{
}

void ModelSystem::Draw(int layerNum)
{
	for (Entity entity : entities_)
	{
		Coordinator::GetComponent<Test_Model_ECSver>(entity).Draw(layerNum);
	}
}
	
void ModelSystem::Release()
{
	//for文内で値を消すのでコピーして回す
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		
		Coordinator::RemoveComponent<Test_Model_ECSver>(entity);
		Coordinator::DestroyEntity(entity);
	}
}

void ModelSystem::CheckRemove()
{
	//for文内で値を消すのでコピーして回す
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		//アタッチされてるオブジェクトが死んでたら
		if (Coordinator::GetComponent<Test_Model_ECSver>(entity).GetAttachedObject()->IsDead())
			Coordinator::RemoveComponent<Test_Model_ECSver>(entity);
	}
}
