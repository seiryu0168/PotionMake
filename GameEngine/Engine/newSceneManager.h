#pragma once
#include<vector>
#include<string>
#include<utility>
#include"../Scenes/SceneBase.h"
#include "Systems/ImageSystem.h"
enum class SCENE_ID
{
	TITLE = 0,
	MENU,
	PLAY,
	RESULT,
	//MAX,
};

namespace newSceneManager
{
	//ECS�̏�������V�[���̏��������s��
	void Initialize();
	//void Initialize(const std::string& name);
	//�V�[���̃A�b�v�f�[�g
	void Update();
	//�`��
	void Draw();
	//�R���|�[�l���g��I�u�W�F�N�g������ł邩�ǂ����m�F
	void CheckRemoveObject();
	//�V�[���ǉ�(�������@�\)
	void AddScene(const std::string& objectFileName);
	//�V�[���쐬(�������@�\)
	void CreateScene(const std::string& sceneName);
	//void ChangeScene(SCENE_ID next, int countDown = 0);
	//�V�[���؂�ւ�
	void ChangeScene(const SCENE_ID& sceneId, int countDown = 0);
	void ChangeScene(const SCENE_ID& sceneId, float countDown);
	//ECS�A�[�L�e�N�`���̏�����
	void ECSInitialize();
	void Release();

	std::shared_ptr<ImageSystem> GetImageSystem();
};

