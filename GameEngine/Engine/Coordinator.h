#pragma once
#include"ECS/ComponentManager.h"
#include"ECS/EntityManager.h"
#include"ECS/SystemManager.h"
#include<unordered_map>
#include"ECS/ECS.h"
#include"ECS/System.h"

namespace Coordinator
{
	extern std::unique_ptr<ComponentManager> componentManager_;
	extern std::unique_ptr<EntityManager> entityManager_;
	extern std::unique_ptr<SystemManager> systemManager_;

	//èâä˙âª
	void Init();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void AllRemove();
	void SystemsUpdate();

	template <typename T>
	void RegisterComponent()
	{
		componentManager_->RegisterComponent<T>();
	}

	template <typename T>
	void AddComponent(Entity entity, const T& component)
	{
		componentManager_->AddComponent<T>(entity, component);
		Signature signature = entityManager_->GetSignature(entity);
		signature.set(componentManager_->GetComponentType<T>(), true);
		entityManager_->SetSignature(entity, signature);

		systemManager_->EntitySignatureChanged(entity, signature);

	}

	template <typename T>
	void RemoveComponent(Entity entity)
	{	
		componentManager_->RemoveComponent<T>(entity);
		Signature signature = entityManager_->GetSignature(entity);
		signature.set(componentManager_->GetComponentType<T>(), false);
		entityManager_->SetSignature(entity, signature);

		systemManager_->EntitySignatureChanged(entity, signature);
	}

	template <typename T>
	T& GetComponent(Entity entity)
	{
		return componentManager_->GetComponent<T>(entity);
	}

	template <typename T>
	ComponentType GetComponentType()
	{
		return componentManager_->GetComponentType<T>();
	}
	template <typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return systemManager_->RegisterSistem<T>();
	}
	template <typename T>
	void SetSystemSignature(const Signature& signature)
	{
		systemManager_->SetSignature<T>(signature);
	}

	template <typename T>
	T* GetSystem()
	{
		return (T*)systemManager_->GetSystem<T>();
	}



 };

