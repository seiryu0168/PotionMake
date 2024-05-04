#include "Camera.h"

Camera::Camera()
	:angleOfView_(XM_PIDIV4),
	aspectRadio_(1),
	billBoardMatrix_(XMMatrixIdentity()),
	nearClipping_(1.0f),
	farClipping_(100.0f),
	position_(XMVectorZero()),
	projMatrix_(XMMatrixIdentity()),
	target_(XMVectorZero()),
	upVector_(XMVectorSet(0,1,0,0)),
	viewMatrix_(XMMatrixIdentity()),
	viewPort_()
{
}

void Camera::Initialize(float width, float height, float nearClipping, float farClipping)
{
	position_ = XMVectorSet(0, 10, -40, 0);	//カメラの位置
	target_ = XMVectorSet(0, 0, 1, 0);	//カメラの焦点
	upVector_ = XMVectorSet(0, 1, 0, 0);
	angleOfView_ = XM_PIDIV4;
	aspectRadio_ = (FLOAT)width / (FLOAT)height;
	nearClipping_ = nearClipping;
	farClipping_ = farClipping;
	// プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)width / (FLOAT)height, 0.1f, 1000.0f);
}

void Camera::Update()
{
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, upVector_);

	billBoardMatrix_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), target_ - position_, upVector_);
	billBoardMatrix_ = XMMatrixInverse(nullptr, billBoardMatrix_);
}

void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;
}

void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

void Camera::SetUpVector(XMVECTOR upVector)
{
	upVector_ = upVector;
}

void Camera::SetProjection(float aov, float aspectRadio, float nearZ, float farZ)
{
	projMatrix_ = XMMatrixPerspectiveFovLH(aov, aspectRadio, nearZ, farZ);
}

void Camera::SetAOV(float aov)
{
	projMatrix_ = XMMatrixPerspectiveFovLH(aov, aspectRadio_, nearClipping_, farClipping_);
}

void Camera::SetAspectRadio(float aspect)
{
	projMatrix_ = XMMatrixPerspectiveFovLH(angleOfView_, aspect, nearClipping_, farClipping_);
}

void Camera::SetClipping(float nearZ, float farZ)
{
	projMatrix_ = XMMatrixPerspectiveFovLH(angleOfView_, aspectRadio_, nearZ, farZ);
}

void Camera::SetViewPort(float width, float height, float minDepth, float maxDepth, float topLeftX, float topLeftY)
{
	viewPort_.Width = width;
	viewPort_.Height = height;
	viewPort_.MinDepth = minDepth;
	viewPort_.MaxDepth = maxDepth;
	viewPort_.TopLeftX = topLeftX;
	viewPort_.TopLeftY = topLeftY;
}

const XMFLOAT3& Camera::GetPosition()
{
	return StoreFloat3(position_);
}	