#pragma once
#include<d3d11.h>
#include<DirectXMath.h>
#include"../Components/Transform.h"
#include"../Coordinator.h"
using namespace DirectX;

//前方宣言
class GameObject;

class ColliderSystem;

struct HitBox
{
	XMFLOAT3 size_;
};

struct HitSphere
{
	float radius_;
};

struct Hit_Capsule
{
	float length_;
	float radius_;
	const XMVECTOR& GetVec() { return dirVec_; }
private:
	XMVECTOR dirVec_;
};

struct HitBox_OBB
{
public:
	XMFLOAT3 size_;

	XMVECTOR vecX_;
	XMVECTOR vecY_;
	XMVECTOR vecZ_;

	float prjLine(XMVECTOR* sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3 = nullptr)
	{
		XMVECTOR sp = XMVectorZero();
		sp = XMVector3Normalize(*sep);
		float r1 = abs(XMVectorGetX(XMVector3Dot(sp, *e1)));
		float r2 = abs(XMVectorGetX(XMVector3Dot(sp, *e2)));
		float r3 = e3 ? abs(XMVectorGetX(XMVector3Dot(sp, *e3))) : 0;

		return r1 + r2 + r3;
	}

	void CalcAxisVec(XMVECTOR rotate)
	{
		//XMVECTOR rotateQua = XMQuaternionRotationMatrix(GetpColObject()->GetTransform().GetWorldRotateMatrix());
		vecX_ = XMVector3Rotate(XMVectorSet(1,0,0,0), rotate);
		vecY_ = XMVector3Rotate(XMVectorSet(0,1,0,0), rotate);
		vecZ_ = XMVector3Rotate(XMVectorSet(0,0,1,0), rotate);
	}
};


enum class ColliderType
{
	BOX_COLLIDER,
	SPHERE_COLLIDER,
	CAPSULE_COLLIDER,
	OBB_COLLIDER,
	COLLIDER_MAX
};

//当たり判定
class Collider
{
private:
	friend class ColliderSystem;
	//friend class Test_BoxCollider_ECSver;
	XMFLOAT3     center_;		//原点
	XMFLOAT3	 leftUpBack_;	//当たり判定の左上奧
	XMFLOAT3	 rightDownFront;//当たり判定の右下手前
	Entity	colliderEntity_;
	ColliderType colliderType_;
	float collisionDistanceLimit_;
	bool isKill_;
	GameObject* attachObject_;
	bool prevHit_;
	bool nowHit_;
	bool SetPrevHit(bool hit) { prevHit_ = hit; };
	bool SetNowHit(bool hit) { nowHit_ = hit; };
public:
	bool isShowHitArea_;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Collider();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="centerPos">コライダーの中心</param>
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
	//コライダーのサイズを返す
	void SetCollisionDistance(float dist) { collisionDistanceLimit_ = dist; }
	//今ヒットしてるかどうか設定(未完成機能)
	void HitEnable(bool isHit) { nowHit_ = isHit; }
	//ヒットしてるかどうか
	bool IsHit() const { return nowHit_; }
	//コライダーを消す
	void KillCollider() { isKill_ = true; }

	bool IsKill() const { return isKill_; }
	bool IsPrevHit() { return prevHit_; };
	bool IsNowHit() { return nowHit_; };
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
	void MortonOrderSolver();
	int GetAccessNumber();
	int GetMortonOrderNumber(XMFLOAT3 pos);
	int BitSeparate(int n);

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

