#pragma once
#include<bitset>
#include<queue>
#include<array>
#include"ECS.h"
//using Entity = unsigned int;
//const Entity MAX_ENTITIES = 5000;
//using ComponentType = unsigned int;
//const ComponentType MAX_COMPONENTS = 32;
//using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
private:
	//使用可能なエンティティのキュー
	std::queue<Entity> availableEntites_{};
	//エンティティで管理されるシグネチャの配列
	std::array<Signature, MAX_ENTITIES> signatures_{};
	//今使用してるエンティティの数
	unsigned int livingEntityCount_{};
public:
	EntityManager();
	~EntityManager();

	//エンティティの有効化
	Entity CreateEntity();
	//エンティティを無効化
	void DestroyEntity(const Entity& entity);
	/// <summary>
	/// シグネチャをセット
	/// </summary>
	/// <param name="entity">シグネチャをセットする配列のインデックス</param>
	/// <param name="signature">セットするシグネチャ</param>
	void SetSignature(const Entity& entity, const Signature& signature);
	/// <summary>
	/// シグネチャの取得
	/// </summary>
	/// <param name="entity">欲しいシグネチャのインデックス</param>
	/// <returns>シグネチャ</returns>
	Signature GetSignature (const Entity& entity) const;
	//初期化
	void Initialize();

};

