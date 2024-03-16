#pragma once
#include<string>
#include<typeinfo>
#include<memory>
#include<list>
#include"Object.h"
#include<vector>
#include"../Components/Transform.h"

class GameObject : public Object
{
	//friend class Collider;
	//friend class Component;
protected:

	bool drawFlag_;						//描画するかどうか

public:
	GameObject();
	GameObject(Object* parent, const std::string& name);
	virtual ~GameObject() {};

	bool IsDraw() const { return drawFlag_; }
	void SetDrawFlag(bool flag) { drawFlag_ = flag; }

	///////////////////////////衝突関連の関数////////////////////////
	virtual void OnCollisionEnter(GameObject* pTarget) {};
	virtual void OnCollisionExit(GameObject* pTarget) {};
	virtual void OnCollisionStay(GameObject* pTarget) {};
	void Collision(GameObject* pTarget);
	void CheckLillCollider(GameObject*);
	//void AddCollider(Collider* collider);
	//void DelCollider(const GameObject& obj);

///////////////////////////各セッターゲッター//////////////////////////////////////
	//void SetTag(const std::string& tagName) { objectTag_ = tagName; }
	//void SetActive(bool status);
	//void SetUpdate(bool status) { isUpdate_ = status; };
	//void SetStart(bool status) { startFlag_ = status; }
	//void SetParent(GameObject* parent);
	//std::string GetTag() const { return objectTag_; }

	//Transform* GetTransform() const;
	/*XMFLOAT3  GetPosition();
	XMFLOAT3  GetRotate();
	XMFLOAT3  GetScale();*/

	//指定した座標に回転させる行列を作る関数
	XMMATRIX LookAtMatrix(const XMFLOAT3& target, const XMVECTOR& frontVec, const XMVECTOR& upVec = XMVectorSet(0, 1, 0, 0));
	XMMATRIX    GetWorldMatrix();

	//ワールド座標取得
	XMFLOAT3    GetWorldPosition() const { return Transform::Float3Add(((GameObject*)GetParent())->transform_->position_, transform_->position_); }

};