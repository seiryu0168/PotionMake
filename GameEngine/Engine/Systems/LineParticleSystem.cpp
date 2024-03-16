#include "LineParticleSystem.h"
#include"../Coordinator.h"
LineParticleSystem::LineParticleSystem() : System()
{
}

void LineParticleSystem::Update()
{
	for (Entity entity : entities_)
	{
		Coordinator::GetComponent<LineParticle>(entity).Update();
	}
}

void LineParticleSystem::Draw(int layerNum)
{
	for (Entity entity : entities_)
	{
		Coordinator::GetComponent<LineParticle>(entity).Draw(layerNum);
	}
}

void LineParticleSystem::Release()
{
	//for�����Œl�������̂ŃR�s�[���ĉ�
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::RemoveComponent<LineParticle>(entity);
		Coordinator::DestroyEntity(entity);
	}

}

void LineParticleSystem::CheckRemove()
{
	//for�����Œl�������̂ŃR�s�[���ĉ�
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		//�A�^�b�`����Ă�I�u�W�F�N�g������ł���
		if (Coordinator::GetComponent<LineParticle>(entity).GetAttachedObject()->IsDead())
			Coordinator::RemoveComponent<LineParticle>(entity);
	}
}
