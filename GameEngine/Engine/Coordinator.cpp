#include "Coordinator.h"
namespace Coordinator
{
	std::unique_ptr<ComponentManager> componentManager_;
	std::unique_ptr<EntityManager> entityManager_;
	std::unique_ptr<SystemManager> systemManager_;

	void Coordinator::Init()
	{
		//各マネージャーのポインタ作成
		componentManager_ = std::make_unique<ComponentManager>();
		entityManager_ = std::make_unique<EntityManager>();
		systemManager_ = std::make_unique<SystemManager>();
	}

	Entity Coordinator::CreateEntity()
	{
		//エンティティ作成
		return entityManager_->CreateEntity();
	}

	void Coordinator::DestroyEntity(Entity entity)
	{
		//エンティティを破壊
		entityManager_->DestroyEntity(entity);
		//エンティティが破壊されたので各マネージャー経由でコンポーネントとシステムに通知
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