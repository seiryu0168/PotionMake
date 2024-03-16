#pragma once
#include"IComponentArray.h"
#include<unordered_map>
template<typename T>
class ComponentArray : public IComponentArray
{
private:
	//コンポーネントの配列(MAX_ENTITIESが配列の長さ)
	std::array<T, MAX_ENTITIES> componentArray_;
	
	//エンティティとインデックスはお互いの値が配列のどこにあるかを値として保持している
	//エンティティから配列のインデックスの	マッピング
	std::unordered_map<Entity, size_t> entityToIndexMap_;
	//インデックスからエンティティのマッピング
	std::unordered_map<size_t, Entity> indexToEntityMap_;
	//配列内の有効なエンティティの総数
	size_t size_;
public:
	void InsertData(const Entity& entity, const T& component) 
	{
		//同じエンティティに複数のコンポーネントが追加されてはいけない
		assert(entityToIndexMap_.find(entity) == entityToIndexMap_.end() && "Component added to same entity more than once");

		//エンティティとインデックスの配列にそれぞれマッピングし、コンポーネントの配列に追加する
		size_t newIndex = size_;
		entityToIndexMap_[entity] = newIndex;
		indexToEntityMap_[newIndex] = entity;
		componentArray_[newIndex] = component;
		++size_;
	}
	void RemoveData(const Entity& entity)
	{
		assert(entityToIndexMap_.find(entity) != entityToIndexMap_.end() && "Removing non-existent component");

		//末尾の要素を削除する要素の場所にコピー
		//消したいコンポーネントのインデックス
		size_t indexOfRemovedEntity = entityToIndexMap_[entity];
		//末尾のインデックス
		size_t indexOfLastElement = size_ - 1;
		//消す予定の場所に末尾の値を代入
		componentArray_[indexOfRemovedEntity] = componentArray_[indexOfLastElement];

		//エンティティ配列の末尾の値
		Entity entityOflastElement = indexToEntityMap_[indexOfLastElement];
		//エンティティ配列末尾の値(インデックス)を消したいエンティティのインデックスに書き換える
		entityToIndexMap_[entityOflastElement] = indexOfRemovedEntity;
		//インデックス配列内の消す値を末尾の要素で書き換える
		indexToEntityMap_[indexOfRemovedEntity] = entityOflastElement;
		//エンティティ配列から消す
		entityToIndexMap_.erase(entity);
		//インデックス配列から最後の値を消す
		indexToEntityMap_.erase(indexOfLastElement);
		//有効なエンティティを一つ減らす
		--size_;
	}
	void Clear() override
	{
		//T dummy;
		//componentArray_.fill(dummy);
		//entityToIndexMap_.clear();
		//indexToEntityMap_.clear();
		//size_ = 0;	
	}
	T& GetData(const Entity& entity)
	{
		assert(entityToIndexMap_.find(entity) != entityToIndexMap_.end() && "Retrieving non-existent component");
		//指定されたエンティティを返す
		return componentArray_[entityToIndexMap_[entity]];
	}
	void EntityDestroyed(const Entity& entity) override
	{
		//指定したエンティティを消す
		if (entityToIndexMap_.find(entity) != entityToIndexMap_.end())
			RemoveData(entity);
	}
};
