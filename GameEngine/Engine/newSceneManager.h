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
	PLAY_MANAGEMENT,
	PLAY_COLLECTION,
	PLAY,
	RESULT,
	//MAX,
};

namespace newSceneManager
{
	//ECSの初期化やシーンの初期化を行う
	void Initialize();
	//void Initialize(const std::string& name);
	//シーンのアップデート
	void Update();
	//描画
	void Draw();
	//コンポーネントやオブジェクトが死んでるかどうか確認
	void CheckRemoveObject();
	//シーン追加(未完成機能)
	void AddScene(const std::string& objectFileName);
	//シーン作成(未完成機能)
	void CreateScene(const std::string& sceneName);
	//void ChangeScene(SCENE_ID next, int countDown = 0);
	//シーン切り替え
	void ChangeScene(const SCENE_ID& sceneId, int countDown = 0);
	void ChangeScene(const SCENE_ID& sceneId, float countDown);
	//ECSアーキテクチャの初期化
	void ECSInitialize();
	std::string GetCurrentSceneName();
	void Release();

	std::shared_ptr<ImageSystem> GetImageSystem();
};

