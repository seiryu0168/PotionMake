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
	//キューの先頭から使用可能なIDを取得
	Entity id = availableEntites_.front();
	//今とったIDは使用するのでキューから出す
	availableEntites_.pop();
	++livingEntityCount_;

	return id;
}

void EntityManager::DestroyEntity(const Entity& entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	//エンティティで配列内から無効化するシグネチャを選び、無効化
	signatures_[entity].reset();
	//シグネチャを無効化したので、エンティティがどこにも属さなくなった。
	//キューに戻す
	availableEntites_.push(entity);

	--livingEntityCount_;
}

void EntityManager::SetSignature(const Entity& entity, const Signature& signature)
{
	assert(entity < MAX_ENTITIES &&"Entity out of range");
	//シグネチャを配列に登録
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
	//キューを使用可能なID(エンティティ)で初期化
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		availableEntites_.push(entity);
	}
	signatures_.fill(0);
	livingEntityCount_ = 0;
}
