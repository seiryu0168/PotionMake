#pragma once
#include "GameObject/GameObject.h"
#include"../SceneBase.h"
enum class SCENE_ID
{
	SCENE_ID_MAIN = 0,
	SCENE_ID_SUB,
};

class SceneManager : public GameObject
{
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;
	bool isSceneChange_;
	UINT countDown_;
public:
	SceneManager(Object* parent);

	void Initialize() override;
	void Update() override;
	void Release() override;

	void ChangeScene(SCENE_ID sceneID, UINT count = 0);
	int GetCountDown() const { return countDown_; }
	SCENE_ID GetCurrentSceneID() const { return currentSceneID_; }
	SCENE_ID GetNextSceneID() const { return nextSceneID_; }
	bool IsSceneChange() const { return isSceneChange_; }
	void ECSInitialize();
	GameObject* CurrentScene();
};

