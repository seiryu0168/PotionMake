#pragma once
#include<d3d11.h>
#include<DirectXMath.h>
#include"../Components/Transform.h"
#include"../Coordinator.h"
using namespace DirectX;

//�O���錾
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

//�����蔻��

class Collider
{
private:
	//friend class Test_BoxCollider_ECSver;
	XMFLOAT3     center_;		//���_
	Entity	colliderEntity_;
	ColliderType colliderType_;
	bool isKill_;
	bool prevHit_;
	bool nowHit_;
	GameObject* attachObject_;
public:

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
	//���q�b�g���Ă邩�ǂ����ݒ�(�������@�\)
	void HitEnable(bool isHit) { nowHit_ = isHit; }
	//�q�b�g���Ă邩�ǂ���
	bool IsHit() const { return nowHit_; }
	//�R���C�_�[������
	void KillCollider() { isKill_ = true; }

	bool IsKill() const { return isKill_; }

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

