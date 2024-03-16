#include "EntityManager.h"
#include<assert.h>
EntityManager::EntityManager()
{
	Initialize();
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::CreateEntity()
{
	assert(livingEntityCount_ < MAX_ENTITIES && "Too many entities in existance.");
	//�L���[�̐擪����g�p�\��ID���擾
	Entity id = availableEntites_.front();
	//���Ƃ���ID�͎g�p����̂ŃL���[����o��
	availableEntites_.pop();
	++livingEntityCount_;

	return id;
}

void EntityManager::DestroyEntity(const Entity& entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	//�G���e�B�e�B�Ŕz������疳��������V�O�l�`����I�сA������
	signatures_[entity].reset();
	//�V�O�l�`���𖳌��������̂ŁA�G���e�B�e�B���ǂ��ɂ������Ȃ��Ȃ����B
	//�L���[�ɖ߂�
	availableEntites_.push(entity);

	--livingEntityCount_;
}

void EntityManager::SetSignature(const Entity& entity, const Signature& signature)
{
	assert(entity < MAX_ENTITIES &&"Entity out of range");
	//�V�O�l�`����z��ɓo�^
	signatures_[entity] = signature;
	
}

Signature EntityManager::GetSignature(const Entity& entity) const
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	
	return signatures_[entity];
}

void EntityManager::Initialize()
{
	while (availableEntites_.empty()==false)
	{
		availableEntites_.pop();
	}
	//�L���[���g�p�\��ID(�G���e�B�e�B)�ŏ�����
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		availableEntites_.push(entity);
	}
	signatures_.fill(0);
	livingEntityCount_ = 0;
}
