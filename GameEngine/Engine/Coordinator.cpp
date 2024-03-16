#include "Coordinator.h"
namespace Coordinator
{
	std::unique_ptr<ComponentManager> componentManager_;
	std::unique_ptr<EntityManager> entityManager_;
	std::unique_ptr<SystemManager> systemManager_;

	void Coordinator::Init()
	{
		//�e�}�l�[�W���[�̃|�C���^�쐬
		componentManager_ = std::make_unique<ComponentManager>();
		entityManager_ = std::make_unique<EntityManager>();
		systemManager_ = std::make_unique<SystemManager>();
	}

	Entity Coordinator::CreateEntity()
	{
		//�G���e�B�e�B�쐬
		return entityManager_->CreateEntity();
	}

	void Coordinator::DestroyEntity(Entity entity)
	{
		//�G���e�B�e�B��j��
		entityManager_->DestroyEntity(entity);
		//�G���e�B�e�B���j�󂳂ꂽ�̂Ŋe�}�l�[�W���[�o�R�ŃR���|�[�l���g�ƃV�X�e���ɒʒm
		componentManager_->EntityDestroyed(entity);
		systemManager_->EntityDestroyed(entity);
	
	}

	void AllRemove()
	{
		
		systemManager_->Clear();
		entityManager_->Initialize();
		//componentManager_->AllRemoveComponent();

	}

	void SystemsUpdate()
	{
		systemManager_->AllSystemUpdate();
	}
}