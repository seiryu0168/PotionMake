#pragma once
#include"../DirectX_11/Math.h"
#include<memory>
using namespace DirectX;
class Transform
{
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;	//拡大行列
public:

	XMVECTOR position_;	//位置
	XMVECTOR rotate_;	//向き
	XMFLOAT3 scale_;	//拡大率

	XMVECTOR baseVec_;	//基準となるベクトル

	Transform* pParent_;//親の情報

	//コンストラクタ
	//Transform();
	Transform(Transform* parent = nullptr);

	//デストラクタ
	~Transform();

	//各行列の計算
	void Calclation();
	//回転
	void RotateAxis(const XMVECTOR& axis, float angle);
	void RotateEular(const XMFLOAT3& rotation);

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


	static XMFLOAT3 Float3Add(const XMVECTOR& add1, const XMVECTOR& add2)
	{
		return StoreFloat3(add1 + add2);
	}

	
};

