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
	//for�����Œl�������̂ŃR�s�[���ĉ�
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		
		Coordinator::RemoveComponent<Test_Model_ECSver>(entity);
		Coordinator::DestroyEntity(entity);
	}
}

void ModelSystem::CheckRemove()
{
	//for�����Œl�������̂ŃR�s�[���ĉ�
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		//�A�^�b�`����Ă�I�u�W�F�N�g������ł���
		if (Coordinator::GetComponent<Test_Model_ECSver>(entity).GetAttachedObject()->IsDead())
			Coordinator::RemoveComponent<Test_Model_ECSver>(entity);
	}
}
