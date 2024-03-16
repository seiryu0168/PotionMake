#include"GameObject/RootJob.h"
#include "SceneManager.h"
#include"../MainScene.h"
#include"../SubScene.h"
#include"ResourceManager/Model.h"
//#include"ResourceManager/ImageManager.h"
#include"ResourceManager/Audio.h"
#include"../PhysicsSystem.h"
#include"../TransformSystem.h"
#include"../ColliderSystem.h"
#include"../ModelSystem.h"
#include"../Coordinator.h"


SceneManager::SceneManager(Object* parent) 
	: GameObject(parent, "SceneManager"),
	currentSceneID_(SCENE_ID::SCENE_ID_MAIN),
	nextSceneID_(SCENE_ID::SCENE_ID_MAIN),
	isSceneChange_(false)
{
	currentSceneID_ = SCENE_ID::SCENE_ID_MAIN;
	nextSceneID_ = currentSceneID_;

	ECSInitialize();

}

void SceneManager::Initialize()
{
	Instantiate<MainScene>(this);
}

void SceneManager::Update()
{
	if (isSceneChange_&&countDown_ == 0)
	{
		Coordinator::AllRemove();
		KillAllChildren();
		ModelManager::AllDeleteModelNum();
		ModelManager::Release();
		ImageManager::AllRelease();
		

		//SceneBase* p = nullptr;
		ECSInitialize();
		switch ((SCENE_ID)nextSceneID_)
		{
		case SCENE_ID::SCENE_ID_MAIN:Instantiate<MainScene>(this); break;
		case SCENE_ID::SCENE_ID_SUB:Instantiate<SubScene>(this); break;
		}

		isSceneChange_ = false;
		currentSceneID_ = nextSceneID_;
	}
	countDown_--;
}

void SceneManager::Release()
{

}
void SceneManager::ChangeScene(SCENE_ID sceneID,UINT count)
{	
	nextSceneID_ = sceneID;
	countDown_ = count;
	isSceneChange_ = true;
}

void SceneManager::ECSInitialize()
{
	//Coordinator::RegisterSystem<PhysicsSystem>();
	//Coordinator::RegisterSystem<TransformSystem>();
	//Coordinator::RegisterSystem<ColliderSystem>();
	//Coordinator::RegisterSystem<ModelSystem>();
	//Coordinator::RegisterComponent<Collider>();
	//Coordinator::RegisterComponent<DrawComponent>();
	//
	//Coordinator::RegisterComponent<Transform>();
	//
	//Signature phy_signature;
	//phy_signature.set(Coordinator::GetComponentType<Gravity>());
	//phy_signature.set(Coordinator::GetComponentType<RigidBody>());
	//phy_signature.set(Coordinator::GetComponentType<TransformData>());
	//
	//Signature trans_signature;
	//trans_signature.set(Coordinator::GetComponentType<Transform>());
	//Signature coll_signature;
	//coll_signature.set(Coordinator::GetComponentType<Collider>());
	//Signature model_signature;
	//model_signature.set(Coordinator::GetComponentType<DrawComponent>());
	//
	//Coordinator::SetSystemSignature<PhysicsSystem>(phy_signature);
	//Coordinator::SetSystemSignature<TransformSystem>(trans_signature);
	//Coordinator::SetSystemSignature<ColliderSystem>(coll_signature);
	//Coordinator::SetSystemSignature<ModelSystem>(model_signature);
}
