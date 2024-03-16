#include "Transform.h"

//コンストラクタ
//Transform::Transform()
//	:matTranslate_(XMMatrixIdentity()),
//	matRotate_(XMMatrixIdentity()),
//	matScale_(XMMatrixIdentity()),
//	position_(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)),
//	rotate_(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)),
//	scale_(XMFLOAT3(1.0f, 1.0f, 1.0f)),
//	baseVec_(XMVectorSet(0, 0, 0, 0)),
//	pParent_(nullptr)
//{
//
//}

Transform::Transform(Transform* parent)
	:matTranslate_(XMMatrixIdentity()),
	matRotate_(XMMatrixIdentity()),
	matScale_(XMMatrixIdentity()),
	position_(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)),
	rotate_(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)),
	scale_(XMFLOAT3(1.0f, 1.0f, 1.0f)),
	baseVec_(XMVectorSet(0, 0, 0, 0)),
	pParent_(parent)
{

}

//デストラクタ
Transform::~Transform()
{

}

//各行列の計算
void Transform::Calclation()
{
	//移動行列
	XMFLOAT3 position = StoreFloat3(position_);
	matTranslate_ = XMMatrixTranslation(position.x, position.y, position.z);
	
	//回転行列
	matRotate_ = XMMatrixRotationQuaternion(rotate_);
	
	//拡大行列
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

void Transform::RotateAxis(const XMVECTOR& axis, float angle)
{

	rotate_ = XMQuaternionRotationNormal(axis, angle);
}

void Transform::RotateEular(const XMFLOAT3& rotation)
{
	rotate_ = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(rotation.x),
											   XMConvertToRadians(rotation.y),
											   XMConvertToRadians(rotation.z));
}

float Transform::GetPositionX()
{
	return position_.m128_f32[0];
}

float Transform::GetPositionY()
{
	return position_.m128_f32[1];
}

float Transform::GetPositionZ()
{
	return position_.m128_f32[2];
}

//逆行列の計算
XMMATRIX Transform::GetNormalMatrix() const
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}

//ワールド行列を取得
XMMATRIX Transform::GetWorldMatrix()
{
	Calclation();
	if (pParent_)
	{
		return matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}
	return matScale_ * matRotate_ * matTranslate_;

}
XMMATRIX Transform::GetLocalMatrix() const
{
	return matScale_ * matRotate_ * matTranslate_;
}
XMMATRIX Transform::GetLocalTranslateMatrix() const
{
	return matTranslate_;
}

XMMATRIX Transform::GetLocalRotateMatrix() const
{
	return matRotate_;
}
XMMATRIX Transform::GetLocalScaleMatrix() const
{
	return matScale_;
}


XMMATRIX Transform::GetWorldTranslateMatrix()
{
	Calclation();
	if (pParent_)
	{
		return matTranslate_ * pParent_->GetLocalTranslateMatrix();
	}
	return matTranslate_;
}

XMMATRIX Transform::GetWorldRotateMatrix()
{
	Calclation();
	if (pParent_)
	{
		return matRotate_ * pParent_->GetLocalRotateMatrix();
	}
	return matRotate_;
}
XMMATRIX Transform::GetWorldScaleMatrix()
{
	Calclation();
	if (pParent_)
	{
		return matScale_ * pParent_->GetLocalScaleMatrix();
	}
	return matScale_;
}

const XMVECTOR& Transform::GetWorldFrontVector()
{
	return baseVec_ * GetWorldRotateMatrix();
}

const XMVECTOR& Transform::GetLocalFrontVector()
{
	return baseVec_ * GetLocalRotateMatrix();
}
