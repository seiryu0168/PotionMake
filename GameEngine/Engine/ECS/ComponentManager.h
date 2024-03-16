#pragma once
#include<unordered_map>
#include<memory>
#include"ComponentArray.h"
#include"ECS.h"

class ComponentManager
{
private:
	//文字列型ポインタからコンポーネント型へのマッピング
	std::unordered_map<const char*, ComponentType> componentTypes_{};
	//文字列型ポインタからコンポーネント配列へのマッピング
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays_{};
	//次に登録するコンポーネントのタイプ
	ComponentType nextComponentType_{};
	//コンポーネント配列の取得
	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray() const
	{
		//コンポーネント
		const char* typeName = typeid(T).name();
		assert(componentTypes_.find(typeName) != componentTypes_.end()&&"Component not registered before use");
		return std::static_pointer_cast<ComponentArray<T>>(componentArrays_.at(typeName));
	}

public:
	//コンポーネントの登録
	template <typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();
		//同じコンポーネントタイプがある場合、登録しない
		if (componentTypes_.find(typeName) != componentTypes_.end())
			return;
		assert(componentTypes_.find(typeName) == componentTypes_.end() && "Registaring component type more once");
		componentTypes_.insert({ typeName,nextComponentType_ });
		componentArrays_.insert({ typeName, std::make_shared<ComponentArray<T>>()});
		++nextComponentType_;
	}
	/// <summary>
	/// コンポーネントタイプの取得
	/// </summary>
	/// <typeparam name="T">コンポーネントタイプ</typeparam>
	/// <returns>コンポーネントタイプの番号(unsigned int)</returns>
	template <typename T>
	ComponentType GetComponentType() const
	{
		const char* typeName = typeid(T).name();
		assert(componentTypes_.find(typeName) != componentTypes_.end() && "Component not registered before use");
		return componentTypes_.at(typeName);
	
	}
	/// <summary>
	/// コンポーネントの追加
	/// エンティティと紐づけられてコンポーネントが追加される
	/// </summary>
	/// <typeparam name="T">コンポーネントタイプ</typeparam>
	/// <param name="entity">追加するエンティティ</param>
	/// <param name="component">追加するコンポーネント</param>
	template <typename T>
	void AddComponent(const Entity& entity, const T& component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}
	/// <summary>
	/// コンポーネント削除
	/// </summary>
	/// <typeparam name="T">コンポーネントタイプ</typeparam>
	/// <param name="entity">消去するコンポーネントに紐づけられたエンティティ</param>
	template <typename T>
	void RemoveComponent(const Entity& entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}
	//コンポーネント全部消す
	void AllRemoveComponent();
	/// <summary>
	/// コンポーネント取得
	/// </summary>
	/// <typeparam name="T">コンポーネントタイプ</typeparam>
	/// <param name="entity">欲しいコンポーネントに紐づけられたエンティティ</param>
	/// <returns>コンポーネント</returns>
	template <typename T>
	T& GetComponent(const Entity& entity) const
	{
		return GetComponentArray<T>()->GetData(entity);
	}
	/// <summary>
	/// エンティティを無効化
	/// </summary>
	/// <param name="entity">無効化したいエンティティ</param>
	void EntityDestroyed(const Entity& entity)
	{
		for (auto const& pair : componentArrays_)
		{
			auto const& component = pair.second;
			component->EntityDestroyed(entity);
		}
	}
};

