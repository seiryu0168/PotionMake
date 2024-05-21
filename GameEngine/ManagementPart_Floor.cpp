#include "ManagementPart_Floor.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/ResourceManager/AudioManager.h"
ManagementPart_Floor::ManagementPart_Floor(Object* parent)
	:GameObject(parent,"ManagementPart_Floor"),
	rotate_(0)
{
}

ManagementPart_Floor::~ManagementPart_Floor()
{
}

void ManagementPart_Floor::Initialize()
{
	Direct3D::SetLight({ 1,100,0 }, { 0,0,0 });
	Direct3D::SetLightClip(50, 110);
	Test_Model_ECSver floorModel(this);
	floorModel.Load("Assets/Model/House01.fbx");
	AddComponent<Test_Model_ECSver>(floorModel);
	transform_->RotateEular(0, 90, 0);
	transform_->position_ = XMVectorSet(0, 0, 1.4f,0);
	hAudio_BGM_ = AudioManager::Load("Assets/Audio/ManagementPart_BGM.wav",true);

	AudioManager::Play(hAudio_BGM_);

}

void ManagementPart_Floor::Update()
{
	//rotate_ += 1;
	//transform_->RotateEular(0, rotate_, 0);
}

void ManagementPart_Floor::Release()
{
}
