#pragma once
#include<d3d11.h>
#include<DirectXMath.h>
#include"../Components/Transform.h"
#include"../Coordinator.h"
using namespace DirectX;

//�O���錾
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

//�����蔻��
class Collider
{
private:
	friend class ColliderSystem;
	//friend class Test_BoxCollider_ECSver;
	XMFLOAT3     center_;		//���_
	XMFLOAT3	 leftUpBack_;	//�����蔻��̍����
	XMFLOAT3	 rightDownFront;//�����蔻��̉E����O
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
	/// �R���X�g���N�^
	/// </summary>
	Collider();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="centerPos">�R���C�_�[�̒��S</param>
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

	//�A�^�b�`����I�u�W�F�N�g��ݒ�
	void SetAttachObject(GameObject* object) { attachObject_ = object; }
	//�A�^�b�`���Ă�I�u�W�F�N�g��Ԃ�
	GameObject* GetAttachedObject() const { return attachObject_; }
	//�R���C�_�[�̃^�C�v��Ԃ�
	ColliderType GetType() const { return colliderType_; }
	//�R���C�_�[�̈ʒu�ݒ�
	void SetCenter(const XMFLOAT3& pos) { center_ = pos; }
	//�R���C�_�[�̈ʒu��Ԃ�
	const XMFLOAT3& GetCenter() const { return center_; }
	//�R���C�_�[�̃T�C�Y��Ԃ�
	void SetCollisionDistance(float dist) { collisionDistanceLimit_ = dist; }
	//���q�b�g���Ă邩�ǂ����ݒ�(�������@�\)
	void HitEnable(bool isHit) { nowHit_ = isHit; }
	//�q�b�g���Ă邩�ǂ���
	bool IsHit() const { return nowHit_; }
	//�R���C�_�[������
	void KillCollider() { isKill_ = true; }

	bool IsKill() const { return isKill_; }
	bool IsPrevHit() { return prevHit_; };
	bool IsNowHit() { return nowHit_; };
	void Draw();

	void Release();

	/// <summary>
	/// �R���C�_�[�̌`��ݒ�
	/// </summary>
	/// <typeparam name="T">�R���C�_�[�̌`(BOX��SPHERE)</typeparam>
	/// <param name="colliderShape">�R���C�_�[�̏��</param>
	template<typename T>
	void SetCollider(const T& colliderShape)
	{
		std::string typeName = typeid(T).name();
		SetCollisionType(typeName);
		colliderEntity_ = Coordinator::CreateEntity();
		Coordinator::AddComponent<T>(colliderEntity_,colliderShape);
	}

	/// <summary>
	/// �R���C�_�[����Ԃ�
	/// </summary>
	/// <typeparam name="T">�R���C�_�[�̌`�̌^</typeparam>
	/// <returns>�R���C�_�[�̏��</returns>
	template<typename T>
	T& GetCollisionShape() const
	{
		return Coordinator::GetComponent<T>(colliderEntity_);
	}
	//�R���C�_�[�̌^��ݒ�
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
	
	

	////�Փ˔͈�
	//
	///// <summary>
	///// AABB���m�̓����蔻��
	///// </summary>
	///// <param name="box1">BoxCollider�^</param>
	///// <param name="box2">BoxCollider�^</param>
	///// <returns></returns>
	//bool IsHitBox_Box(BoxCollider* box1, BoxCollider* box2);
	//
	///// <summary>
	///// AABB�Ƌ��̓����蔻��
	///// </summary>
	///// <param name="box">BoxCollider�^</param>
	///// <param name="sphere">SphereCollider�^</param>
	///// <returns></returns>
	//bool IsHitBox_Sphere(BoxCollider* box, SphereCollider* sphere);
	//
	///// <summary>
	///// ���Ƌ��̓����蔻��
	///// </summary>
	///// <param name="sphereA">SphereCollider�^</param>
	///// <param name="sphereB">SphereCollider�^</param>
	///// <returns></returns>
	//bool IsHitSphere_Sphere(SphereCollider* sphereA, SphereCollider* sphereB);
	//
	////bool IsHitSphere_Polygon(SphereCollider* sphereA,std::vector<XMVECTOR> polyList);
	///// <summary>
	///// OBB���m�̓����蔻��
	///// </summary>
	///// <param name="obbA">OBBCollider�^</param>
	///// <param name="obbB">OBBCollider�^</param>
	///// <returns></returns>
	//bool IsHitOBB_OBB(OBBCollider* obbA,OBBCollider* obbB);
	//
	///// <summary>
	///// OBB�Ƌ��̓����蔻��
	///// </summary>
	///// <param name="obb">OBBCollider�^</param>
	///// <param name="sphere">SphereCollider�^</param>
	///// <returns></returns>
	//bool IsHitOBB_Sphere(OBBCollider* obb, SphereCollider* sphere);
	//
	//
	///// <summary>
	///// �����蔻���t�����I�u�W�F�N�g���擾
	///// </summary>
	///// <returns>�����蔻���t�����I�u�W�F�N�g</returns>
	//GameObject* GetpColObject() { return pColObject_; }
	//
	///// <summary>
	///// �����蔻�������I�u�W�F�N�g��ݒ�
	///// </summary>
	///// <param name="gameObject">�C�ӂ̃I�u�W�F�N�g(GameObject�^)</param>
	//void SetGemaObject(GameObject* gameObject) { attachObject_ = gameObject; }

};

