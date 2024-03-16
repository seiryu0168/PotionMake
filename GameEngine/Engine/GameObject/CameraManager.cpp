#include "CameraManager.h"
#include"../DirectX_11/Direct2D.h"

//�ϐ�
XMVECTOR position_;			//�J�����̈ʒu�i���_�j
XMVECTOR target_;			//����ʒu�i�œ_�j
XMVECTOR upVector_;			//��x�N�g��
XMMATRIX viewMatrix_;		//�r���[�s��
XMMATRIX projMatrix_;		//�v���W�F�N�V�����s��
XMMATRIX billBoardMatrix_;	//�r���{�[�h�s��
float	 angleOfView;		//����p
float	 aspectRadio;		//�A�X�y�N�g��
float	 nearClipping;		//�j�A�N���b�s���O
float	 farClipping;		//�t�@�[�N���b�s���O

namespace CameraManager
{
	std::vector<Camera> cameraList_;
	float screenWidth_;
	float screenHeight_;
	int currentViewPort_;

	Camera defaultCamera_;
}

//������
void CameraManager::Initialize(float width,float height)
{
	screenWidth_ = width;
	screenHeight_ = height;
	
	
	position_ = XMVectorSet(0, 10, -40, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_
	upVector_ = XMVectorSet(0, 1, 0, 0);
	angleOfView = XM_PIDIV4;
	aspectRadio = (FLOAT)width / (FLOAT)height;
	nearClipping = 0.1f;
	farClipping = 1000.0f;
	// �v���W�F�N�V�����s��
	//projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)width / (FLOAT)height, 0.1f, 1000.0f);
	defaultCamera_.Initialize(width, height, nearClipping, farClipping);
	defaultCamera_.SetPosition(position_);
	//defaultCamera_.SetTarget(target_);
	//defaultCamera_.SetAOV(angleOfView);
	//defaultCamera_.SetAspectRadio(aspectRadio);
	defaultCamera_.SetViewPort(width, height, 0.0f, 1.0f, 0, 0);
	AddCamera(defaultCamera_);
	//cameraList_.push_back(defaultCamera_);
}

//�X�V
void CameraManager::Update()
{
	for (Camera& camera : cameraList_)
	{
		camera.Update();
	}

	////�r���[�s��̍쐬
	//viewMatrix_ = XMMatrixLookAtLH(position_, target_, upVector_);
	//
	//billBoardMatrix_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), target_ - position_, upVector_);
	//billBoardMatrix_ = XMMatrixInverse(nullptr, billBoardMatrix_);
}

void CameraManager::CreateCamera(XMFLOAT3 pos, XMFLOAT3 target, float aov, float width, float height, float nearClipping, float farClipping)
{
	Camera camera;
	camera.Initialize(width, height, nearClipping, farClipping);
	camera.SetPosition(XMLoadFloat3(&pos));
	camera.SetTarget(XMLoadFloat3(&target));
	camera.SetAOV(aov);

	cameraList_.push_back(camera);
	//position_ = XMVectorSet(0, 10, -40, 0);	//�J�����̈ʒu
	//target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_
	//upVector_ = XMVectorSet(0, 1, 0, 0);
	//angleOfView = XM_PIDIV4;
	//aspectRadio = (FLOAT)width / (FLOAT)height;
	//nearClipping = 0.1f;
	//farClipping = 1000.0f;
	//// �v���W�F�N�V�����s��
	//projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)width / (FLOAT)height, 0.1f, 1000.0f);
}

Camera& CameraManager::GetCamera(UINT num)
{
	if (num >= cameraList_.size())
		num = cameraList_.size() - 1;

		//currentViewPort_ = num;
		return cameraList_[num];
}

Camera& CameraManager::GetCurrentCamera()
{
	return cameraList_[currentViewPort_];
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

void CameraManager::AddCamera(Camera camera)
{
	float a = (camera.GetViewPort().Width / (float)Direct3D::GetScreenWidth());
	int32_t dpiX = ((int32_t)camera.GetViewPort().Width / (float)Direct3D::GetScreenWidth()) * D2D::GetdpiX();
	int32_t dpiY = ((int32_t)camera.GetViewPort().Height / (float)Direct3D::GetScreenHeight()) * D2D::GetdpiY();
	D2D::CreateRenderTarget({ dpiX,dpiY });
	cameraList_.push_back(camera);
}

void CameraManager::AllRmoveCamera(UINT num)
{
	cameraList_.clear();
}

void CameraManager::UpdateCameraNum(int num)
{
	currentViewPort_ = num;
}

int CameraManager::GetCurrentCameraNum()
{
	return currentViewPort_;
}

void CameraManager::ResetCamera()
{
	cameraList_.clear();
	D2D::AllRemoveRenderTarget();
	AddCamera(defaultCamera_);
	//cameraList_.push_back(defaultCamera_);
}

UINT CameraManager::GetCameraCount()
{
	return (UINT)cameraList_.size();
}

////�ʒu��ݒ�
//void CameraManager::SetPosition(XMVECTOR position)
//{
//	position_ = position;
//}
//
////�œ_��ݒ�
//void CameraManager::SetTarget(XMVECTOR target)
//{
//	target_ = target;
//}
//
//void CameraManager::SetUpVector(XMVECTOR upVector)
//{
//	upVector_ = upVector;
//}
//
//void CameraManager::SetProjection(float aov, float aspectRadio, float nearZ, float farZ)
//{
//	projMatrix_ = XMMatrixPerspectiveFovLH(aov, aspectRadio, nearZ, farZ);
//}
//
//void CameraManager::SetAOV(float aov)
//{
//	projMatrix_ = XMMatrixPerspectiveFovLH(aov, aspectRadio, nearClipping, farClipping);
//}
//
//void CameraManager::SetAspectRadio(float aspect)
//{
//	projMatrix_ = XMMatrixPerspectiveFovLH(angleOfView, aspect, nearClipping, farClipping);
//}
//
//void CameraManager::SetClipping(float nearZ, float farZ)
//{
//	projMatrix_ = XMMatrixPerspectiveFovLH(angleOfView, aspectRadio, nearZ, farZ);
//}
//
//
////���_(�J�����̈ʒu)���擾
//XMFLOAT3 CameraManager::GetPosition()
//{
//	return StoreFloat3(position_);
//}
//XMVECTOR CameraManager::GetTarget()
//{
//	return target_;
//}
////�r���[�s����擾
//XMMATRIX CameraManager::GetViewMatrix()
//{
//	return viewMatrix_;
//}
//
//XMMATRIX CameraManager::GetBillBoardMatrix()
//{
//	return billBoardMatrix_;
//}
////�v���W�F�N�V�����s����擾
//XMMATRIX CameraManager::GetProjectionMatrix()
//{
//	return projMatrix_;
//}