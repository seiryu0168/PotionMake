#include "Shooter.h"
#include "../Engine/Systems/ImageSystem.h"
#include"../Easing.h"
#include"../Engine/GameObject/CameraManager.h"
#include"../Engine/DirectX_11/Input.h"
#include"Shooting_Gun.h"
#include"Shooting.h"
namespace
{
	const float TRIGGER_SHOT{ 0.7f };
	XMVECTOR CAMERA_POS[2]{ XMVectorSet(0, 0, -20, 0),XMVectorSet(0, 45, -100, 0) };
	XMVECTOR CAMERA_DEFAULT_POS{ XMVectorSet(0, 50, -100, 0) };
	const XMFLOAT2 ROTATE_LIMIT{ 30,30 };
}
Shooter::Shooter(Object* parent)
	:GameObject(parent,"Shooter"),target_(XMVectorSet(0,0,30,0)),playerNum_(0),
	aimMode_(false), rotate_({0,0})
{
}

Shooter::~Shooter()
{
}

void Shooter::Initialize()
{

	float radius = VectorDot(XMVectorSet(0, 0, 1, 0), XMVector3Normalize(target_));
	transform_->position_ = CAMERA_DEFAULT_POS;
	Image image;
	image.Load("Assets/Image/Image_Shooting_Sight.png");
	AddComponent<Image>(image);
	Instantiate<Shooting_Gun>(this)->SetPlayerNum_(playerNum_);
	CAMERA_POS[0] = transform_->position_;
	CameraManager::GetCamera(playerNum_).SetPosition(CAMERA_POS[1]);
}

void Shooter::Update()
{	
	//�X�e�B�b�N�̓���
	rotate_.x += -Input::GetLStick_Y(playerNum_);
	rotate_.y += Input::GetLStick_X(playerNum_);
	//���͒l�̒���
	rotate_.x = Clamp<float>(rotate_.x, -ROTATE_LIMIT.x, ROTATE_LIMIT.x);
	rotate_.y = Clamp<float>(rotate_.y, -ROTATE_LIMIT.y, ROTATE_LIMIT.y);
	transform_->RotateEular({ rotate_.x,rotate_.y,0 });
	//�J�����̏œ_�x�N�g��
	XMVECTOR dir = XMVector3Rotate(target_, transform_->rotate_);
	//�E�g���K�[�������ꂽ��e�𔭎�
	if (Input::GetRTriggerDown(playerNum_))
	{
		((Shooting_Gun*)FindChild("Shooting_Gun"))->Shot(dir);
	}
	//Y�{�^���������ꂽ�烊���[�h
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y, playerNum_))
		Reload();
	//�J�����̌�����ς���
	CameraManager::GetCamera(playerNum_).SetTarget(CAMERA_POS[1] +dir);
}

void Shooter::ModeChange()
{
	//�G�C�����[�h�������łȂ���
	aimMode_ = !aimMode_;
	((Shooting_Gun*)FindChild("Shooting_Gun"))->SetDraw(!aimMode_);
	if (aimMode_)
	{
		CameraManager::GetCamera(playerNum_).SetPosition(CAMERA_POS[1]);
	}
	else
		CameraManager::GetCamera(playerNum_).SetPosition(CAMERA_POS[aimMode_]);

}

void Shooter::Reload()
{
	//�e�N���X���Ăяo���ă����[�h
	Shooting_Gun* gun = (Shooting_Gun*)FindChild("Shooting_Gun");
	int score = gun->GetShotCount();
	gun->Reload();
}

void Shooter::Release()
{
}
