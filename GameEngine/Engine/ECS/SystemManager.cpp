#include "SystemManager.h"

void SystemManager::EntityDestroyed(Entity entity)
{
	//各システムからエンティティを消去
	//entities_は
	for (auto const& pair : systems_)
	{
		auto const& system = pair.second;
		system->entities_.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, const Signature entitySignature)
{
	//各システムにエンティティのシグネチャが変更されたことを通知
	for (auto const& pair : systems_)
	{
		auto const& type = pair.first;
			auto const& system = pair.second;
		auto const& systemSignature = signatures_.at(type);
		//エンティティのシグネチャがシステムのシグネチャと一致するなら
		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->entities_.insert(entity);
		}
		//一致しない場合
		else
		{
			system->entities_.erase(entity);
		}
	}	
}

void SystemManager::AllSystemUpdate()
{
	for (auto& system : systems_)
	{
		system.second->Update();
	}
}

void SystemManager::Clear()
{
	for (auto&& itr : systems_)
	{
		itr.second->Release();
	}
	//signatures_.clear();
	//systems_.clear();
}
