#pragma once
#include"../DirectX_11/Math.h"
#include<memory>
#include<List>
using namespace DirectX;
class Object;
class Transform
{
	Object* attachObject_;
	bool isDead_;
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;	//拡大行列
	XMVECTOR front_;
	XMVECTOR right_;
	XMVECTOR left_;
	XMVECTOR back_;
public:

	XMVECTOR position_;	//位置
	XMVECTOR rotate_;	//向き
	XMFLOAT3 scale_;	//拡大率

	XMVECTOR baseVec_;	//基準となるベクトル

	Transform* pParent_;//親の情報
	std::list<Transform*> childList_;

	//コンストラクタ
	//Transform();
	Transform(Object* obj = nullptr,Transform* parent = nullptr);

	//デストラクタ
	~Transform();

	void PushBackChild(Transform* child);

	//各行列の計算
	void Calclation();

	//更新
	void Update();

	void UpdateSub();
	//回転
	void RotateAxis(const XMVECTOR& axis, float angle);
	void RotateEular(const XMFLOAT3& rotation);
	void RotateEular(float x,float y,float z);

	Object* GetAttachedObject() const { return attachObject_; }

	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();
	//回転行列と拡縮の逆行列の計算
	XMMATRIX GetNormalMatrix() const;
	
	//ワールド行列を取得
	XMMATRIX GetWorldMatrix();
	//各ローカル行列の取得
	XMMATRIX GetLocalMatrix() const;
	XMMATRIX GetLocalTranslateMatrix() const;
	XMMATRIX GetLocalRotateMatrix() const;
	XMMATRIX GetLocalScaleMatrix() const;

	//各ワールド行列の取得
	XMMATRIX GetWorldTranslateMatrix();
	XMMATRIX GetWorldRotateMatrix();
	XMMATRIX GetWorldScaleMatrix();

	const XMVECTOR& GetWorldFrontVector();
	const XMVECTOR& GetLocalFrontVector();

	XMVECTOR GetFront() { return front_; }
	XMVECTOR GetRight() { return right_; }
	XMVECTOR GetLeft() { return left_; }
	XMVECTOR GetBack() { return back_; }

	static XMFLOAT3 Float3Add(const XMVECTOR& add1, const XMVECTOR& add2)
	{
		return StoreFloat3(add1 + add2);
	}
	void Dead() { isDead_ = true;}
	bool IsDead() { return isDead_; }
	void RemoveChild();
};

