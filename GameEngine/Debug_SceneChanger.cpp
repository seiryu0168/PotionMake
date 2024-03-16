#include "Debug_SceneChanger.h"
#include"Engine/newSceneManager.h"
#include"Engine/DirectX_11/Input.h"
Debug_SceneChanger::Debug_SceneChanger()
{
}

Debug_SceneChanger::~Debug_SceneChanger()
{
}

void Debug_SceneChanger::Initialize()
{
}

void Debug_SceneChanger::Update()
{
	//�^�C�g���V�[���Ɉړ�
	if (Input::IsKeyDown(DIK_1)) 
	{
		newSceneManager::ChangeScene(SCENE_ID::TITLE);
	}
	//���j���[�V�[���Ɉړ�
	if (Input::IsKeyDown(DIK_2))
	{
		newSceneManager::ChangeScene(SCENE_ID::MENU);
	}
	//�Q�[���v���C�V�[���Ɉړ�
	if (Input::IsKeyDown(DIK_3))
	{
		newSceneManager::ChangeScene(SCENE_ID::PLAY);
	}

}

void Debug_SceneChanger::Release()
{
}
