#include"../Scenes/Scene_Title.h"
#include"../Scenes/Scene_Menu.h"
#include"../Scenes/Scene_Play_ManagementPart.h"
#include"../Scenes/Scene_Play_CollectionPart.h"
#include"../Scenes/Scene_Play.h"
#include"../Scenes/Scene_Result.h"

#include"ResourceManager/ModelManager_ECSver.h"
#include"ResourceManager/ImageManager_ECSver.h"
#include"ResourceManager/Audio.h"
#include"ResourceManager/TextureManager.h"

#include"Systems/PhysicsSystem.h"
#include"Systems/TransformSystem.h"
#include"Systems/ColliderSystem.h"
#include"Systems/ModelSystem.h"
#include"Systems/ParticleSystem.h"
#include"Systems/LineParticleSystem.h"
#include"Systems/TextSystem.h"
#include"Systems/ImageSystem.h"

#include"GameObject/CameraManager.h"
#include"../StaticResource.h"

#include"Coordinator.h"
#include "newSceneManager.h"
#include"../InterSceneData.h"
#include "ResourceManager/Audio.h"
#include "../Division.h"

//変数
namespace
{
	SCENE_ID prevSceneName_;
	SCENE_ID currentSceneName_;
	SCENE_ID nextSceneName_;
	bool isSceneChange_;
	UINT changeCount_;
	std::string sceneFile_;
	std::unordered_map<SCENE_ID, std::shared_ptr<SceneBase>> sceneList_;
	std::shared_ptr<SceneBase> currentScene_;
	std::shared_ptr<ColliderSystem> pColliderSystem_;
	std::shared_ptr<ModelSystem> pModelSyatem_;
	std::shared_ptr<ParticleSystem> pParticleSystem_;
	std::shared_ptr<LineParticleSystem> pLineParticleSystem_;
	std::shared_ptr<TextSystem> pTextSystem_;
	std::shared_ptr<ImageSystem> pImageSystem_;

	int MAX_LAYER = 4;
}

//外部から見えないようにする
namespace newSceneManager
{
	//シーンリストに要素を格納する
	void SceneInitialize();
}

namespace newSceneManager
{

	void Initialize()
	{
		prevSceneName_ = SCENE_ID::TITLE;
		currentSceneName_ = SCENE_ID::TITLE;
		nextSceneName_ = SCENE_ID::TITLE;
		isSceneChange_ = false;
		changeCount_ = 0;
		ECSInitialize();

		SceneInitialize();

		currentScene_ = sceneList_[currentSceneName_];
		currentScene_->SceneInitialize();
	}

	void Update()
	{
		if (isSceneChange_ && changeCount_ <= 0)
		{
			Division::setLoad(true);
			currentScene_->AllKillObject();
			//オーディオネームスペースの解放
			Audio::Release();
			//オーディオネームスペースの初期化
			Audio::Initialize();
			//コンポーネントの削除
			Coordinator::AllRemove();
			//モデルの解放
			ModelManager_ECSver::Release();
			//画像の解放
			ImageManager_ECSver::Release();
			//テキストの解放
			TextureManager::Release();
			//カメラリセット
			CameraManager::ResetCamera();
			//シーン切り替え
			currentScene_ = sceneList_[nextSceneName_];
			//シーンの初期化
			currentScene_->SceneInitialize();
			//シーン名切り替え
			currentSceneName_ = nextSceneName_;
			isSceneChange_ = false;
			Division::setLoad(false);
		}
		//コライダーの更新
		pColliderSystem_.get()->Update();
		//シーンの更新
		currentScene_->Update();
		//シーンの更新
		currentScene_->StaticUpdate();
		currentScene_->GetRootObject()->GetTransform()->UpdateSub();
		//モデルの更新
		pModelSyatem_->Update();
		//パーティクルの更新
		pParticleSystem_->Update();
		//ラインパーティクルの更新
		pLineParticleSystem_->Update();
		//シーン切り替えのカウントダウン
		if (changeCount_ != 0)
		{
			changeCount_--;
			changeCount_ = max(0, changeCount_);
		}
	}

	void Draw()
	{
		for (int layerCount = 0; layerCount < MAX_LAYER; layerCount++)
		{
			for (int i = 0; i < CameraManager::GetCameraCount(); i++)
			{
				CameraManager::UpdateCameraNum(i);
				Direct3D::SetViewPort(CameraManager::GetCamera(i).GetViewPort());

				
				pModelSyatem_->Draw(layerCount);
				pParticleSystem_->Draw(layerCount);
				pLineParticleSystem_->Draw(layerCount);
				pImageSystem_->Draw(layerCount);
				pTextSystem_->Draw(layerCount);
			}
		}
				pColliderSystem_->Draw();
		CameraManager::UpdateCameraNum(0);
		Direct3D::SetViewPort(CameraManager::GetCamera(0).GetViewPort());
		//StaticResource::Draw();
		currentScene_->Draw();
	}

	void AddScene(const std::string& objectFileName)
	{

	}

	void CreateScene(const std::string& sceneName)
	{
		//Scene1 scene(sceneName);
		//sceneList_.push_back(scene);
	}

	void CheckRemoveObject()
	{
		pColliderSystem_->CheckRemove();
		pModelSyatem_->CheckRemove();
		pParticleSystem_->CheckRemove();
		pLineParticleSystem_->CheckRemove();
		pImageSystem_->CheckRemove();
		pTextSystem_->CheckRemove();
		currentScene_->CheckKillObject();
	}

	void ChangeScene(const SCENE_ID& sceneId, int countDown)
	{
		if (sceneList_.find(sceneId) == sceneList_.end())
			return;
		isSceneChange_ = true;
		nextSceneName_ = sceneId;
		changeCount_ = countDown;
	}
	void ChangeScene(const SCENE_ID& sceneId, float countDown)
	{
		if (sceneList_.find(sceneId) == sceneList_.end())
			return;
		isSceneChange_ = true;
		nextSceneName_ = sceneId;
		changeCount_ = countDown * 60.0f;
	}

	void ECSInitialize()
	{
		//ECSの初期化
		Coordinator::RegisterSystem<PhysicsSystem>();
		Coordinator::RegisterSystem<TransformSystem>();
		pTextSystem_ = Coordinator::RegisterSystem<TextSystem>();
		pModelSyatem_ = Coordinator::RegisterSystem<ModelSystem>();
		pParticleSystem_ = Coordinator::RegisterSystem<ParticleSystem>();
		pLineParticleSystem_ = Coordinator::RegisterSystem<LineParticleSystem>();
		pColliderSystem_ = Coordinator::RegisterSystem<ColliderSystem>();
		pImageSystem_ = Coordinator::RegisterSystem<ImageSystem>();
		Coordinator::RegisterComponent<Text>();
		Coordinator::RegisterComponent<Collider>();
		Coordinator::RegisterComponent<Particle>();
		Coordinator::RegisterComponent<LineParticle>();
		Coordinator::RegisterComponent<Transform>();
		Coordinator::RegisterComponent<Test_Model_ECSver>();
		Coordinator::RegisterComponent<Image>();
		Signature phy_signature;
		phy_signature.set(Coordinator::GetComponentType<Gravity>());
		phy_signature.set(Coordinator::GetComponentType<RigidBody>());
		phy_signature.set(Coordinator::GetComponentType<TransformData>());

		Signature trans_signature;
		trans_signature.set(Coordinator::GetComponentType<Transform>());
		Signature coll_signature;
		coll_signature.set(Coordinator::GetComponentType<Collider>());
		Signature text_signature;
		text_signature.set(Coordinator::GetComponentType<Text>());
		Signature particle_signature;
		particle_signature.set(Coordinator::GetComponentType<Particle>());
		Signature lineParticle_signature;
		lineParticle_signature.set(Coordinator::GetComponentType<LineParticle>());
		Signature model_signature;
		model_signature.set(Coordinator::GetComponentType<Test_Model_ECSver>());
		Signature image_signature;
		image_signature.set(Coordinator::GetComponentType<Image>());

		Coordinator::SetSystemSignature<PhysicsSystem>(phy_signature);
		Coordinator::SetSystemSignature<TransformSystem>(trans_signature);
		Coordinator::SetSystemSignature<ColliderSystem>(coll_signature);
		Coordinator::SetSystemSignature<ParticleSystem>(particle_signature);
		Coordinator::SetSystemSignature<LineParticleSystem>(lineParticle_signature);

		Coordinator::SetSystemSignature<ModelSystem>(model_signature);
		Coordinator::SetSystemSignature<TextSystem>(text_signature);
		Coordinator::SetSystemSignature<ImageSystem>(image_signature);
	}

	std::string GetCurrentSceneName()
	{
		return currentScene_->GetSceneName();
	}

	void Release()
	{
		InterSceneData::AllDelete();
		Division::setLoad(true);
		currentScene_->AllKillObject();

		Coordinator::AllRemove();
		ModelManager_ECSver::Release();
		ImageManager_ECSver::Release();
		ImageManager_ECSver::StaticImageRelease();
		TextureManager::Release();
		TextureManager::StaticTextureRelease();
		//D2D::
		CameraManager::ResetCamera();
		Division::setLoad(false);
	}

	std::shared_ptr<ImageSystem> GetImageSystem()
	{
		return pImageSystem_;
	}

	void SceneInitialize()
	{
		sceneList_.insert({ SCENE_ID::TITLE, std::make_unique<Scene_Title>("Title") });
		sceneList_.insert({ SCENE_ID::MENU, std::make_unique<Scene_Menu>("Menu") });
		sceneList_.insert({ SCENE_ID::PLAY_MANAGEMENT,std::make_unique<Scene_Play_ManagementPart>("Play_ManagementPart")});
		sceneList_.insert({ SCENE_ID::PLAY_COLLECTION,std::make_unique<Scene_Play_CollectionPart>("Play_CollectionPart")});
		sceneList_.insert({ SCENE_ID::PLAY, std::make_unique<Scene_Play>("Play") });
		sceneList_.insert({ SCENE_ID::RESULT, std::make_unique<Scene_Result>("Result") });
	}
}