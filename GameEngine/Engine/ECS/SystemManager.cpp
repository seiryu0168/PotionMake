#include "SystemManager.h"

void SystemManager::EntityDestroyed(Entity entity)
{
	//�e�V�X�e������G���e�B�e�B������
	//entities_��
	for (auto const& pair : systems_)
	{
		auto const& system = pair.second;
		system->entities_.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, const Signature entitySignature)
{
	//�e�V�X�e���ɃG���e�B�e�B�̃V�O�l�`�����ύX���ꂽ���Ƃ�ʒm
	for (auto const& pair : systems_)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = signatures_.at(type);
		//�G���e�B�e�B�̃V�O�l�`�����V�X�e���̃V�O�l�`���ƈ�v����Ȃ�
		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->entities_.insert(entity);
		}
		//��v���Ȃ��ꍇ
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
