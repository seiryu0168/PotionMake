#pragma once
#include<d3d11.h>
#include<DirectXMath.h>
#include"../Components/Transform.h"
#include"../Coordinator.h"
using namespace DirectX;

//前方宣言
class GameObject;

struct HitBox
{
	XMFLOAT3 size_;
};

struct HitSphere
{
	float radius_;
};


enum class ColliderType
{
	BOX_COLLIDER,
	SPHERE_COLLIDER,
	OBB_COLLIDER,
	COLLIDER_MAX

};

//当たり判定

class Collider
{
private:
	//friend class Test_BoxCollider_ECSver;
	XMFLOAT3     center_;		//原点
	Entity	colliderEntity_;
	ColliderType colliderType_;
	bool isKill_;
	bool prevHit_;
	bool nowHit_;
	GameObject* attachObject_;
public:
	bool isShowHitArea_;

	Collider();
	Collider(const XMFLOAT3& centerPos);
	template<typename T>
	Collider(const XMFLOAT3& centerPos, const T& colliderShape)
	{
		center_ = centerPos;
		std::string typeName = typeid(T).name();
		SetCollisionType(typeName);
		colliderEntity_ = Coordinator::CreateEntity();
		Coordinator::AddComponent<T>(colliderEntity_, colliderShape);
	}
	~Collider();

	//アタッチするオブジェクトを設定
	void SetAttachObject(GameObject* object) { attachObject_ = object; }
	//アタッチしてるオブジェクトを返す
	GameObject* GetAttachedObject() const { return attachObject_; }
	//コライダーのタイプを返す
	ColliderType GetType() const { return colliderType_; }
	//コライダーの位置設定
	void SetCenter(const XMFLOAT3& pos) { center_ = pos; }
	//コライダーの位置を返す
	const XMFLOAT3& GetCenter() const { return center_; }
	//今ヒットしてるかどうか設定(未完成機能)
	void HitEnable(bool isHit) { nowHit_ = isHit; }
	//ヒットしてるかどうか
	bool IsHit() const { return nowHit_; }
	//コライダーを消す
	void KillCollider() { isKill_ = true; }

	bool IsKill() const { return isKill_; }

	void Draw();

	void Release();

	/// <summary>
	/// コライダーの形を設定
	/// </summary>
	/// <typeparam name="T">コライダーの形(BOXかSPHERE)</typeparam>
	/// <param name="colliderShape">コライダーの情報</param>
	template<typename T>
	void SetCollider(const T& colliderShape)
	{
		std::string typeName = typeid(T).name();
		SetCollisionType(typeName);
		colliderEntity_ = Coordinator::CreateEntity();
		Coordinator::AddComponent<T>(colliderEntity_,colliderShape);
	}

	/// <summary>
	/// コライダー情報を返す
	/// </summary>
	/// <typeparam name="T">コライダーの形の型</typeparam>
	/// <returns>コライダーの情報</returns>
	template<typename T>
	T& GetCollisionShape() const
	{
		return Coordinator::GetComponent<T>(colliderEntity_);
	}
	//コライダーの型を設定
	void SetCollisionType(const std::string& name);

	//template <typename T>
	//T& GetCollider() const
	//{
	//
	//	return Coordinator::GetComponent<T>(colliderEntity_);
	//}
	
	

	////衝突範囲
	//
	///// <summary>
	///// AABB同士の当たり判定
	///// </summary>
	///// <param name="box1">BoxCollider型</param>
	///// <param name="box2">BoxCollider型</param>
	///// <returns></returns>
	//bool IsHitBox_Box(BoxCollider* box1, BoxCollider* box2);
	//
	///// <summary>
	///// AABBと球の当たり判定
	///// </summary>
	///// <param name="box">BoxCollider型</param>
	///// <param name="sphere">SphereCollider型</param>
	///// <returns></returns>
	//bool IsHitBox_Sphere(BoxCollider* box, SphereCollider* sphere);
	//
	///// <summary>
	///// 球と球の当たり判定
	///// </summary>
	///// <param name="sphereA">SphereCollider型</param>
	///// <param name="sphereB">SphereCollider型</param>
	///// <returns></returns>
	//bool IsHitSphere_Sphere(SphereCollider* sphereA, SphereCollider* sphereB);
	//
	////bool IsHitSphere_Polygon(SphereCollider* sphereA,std::vector<XMVECTOR> polyList);
	///// <summary>
	///// OBB同士の当たり判定
	///// </summary>
	///// <param name="obbA">OBBCollider型</param>
	///// <param name="obbB">OBBCollider型</param>
	///// <returns></returns>
	//bool IsHitOBB_OBB(OBBCollider* obbA,OBBCollider* obbB);
	//
	///// <summary>
	///// OBBと球の当たり判定
	///// </summary>
	///// <param name="obb">OBBCollider型</param>
	///// <param name="sphere">SphereCollider型</param>
	///// <returns></returns>
	//bool IsHitOBB_Sphere(OBBCollider* obb, SphereCollider* sphere);
	//
	//
	///// <summary>
	///// 当たり判定を付けたオブジェクトを取得
	///// </summary>
	///// <returns>当たり判定を付けたオブジェクト</returns>
	//GameObject* GetpColObject() { return pColObject_; }
	//
	///// <summary>
	///// 当たり判定をつけるオブジェクトを設定
	///// </summary>
	///// <param name="gameObject">任意のオブジェクト(GameObject型)</param>
	//void SetGemaObject(GameObject* gameObject) { attachObject_ = gameObject; }

};

