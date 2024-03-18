#include"SceneBase.h"

//#include"PhysicsSystem.h"
//#include"TransformSystem.h"
//#include"ColliderSystem.h"
//#include"ModelSystem.h"
//#include"Coordinator.h"


SceneBase::SceneBase()
	:SceneBase("default")
{
	//debug_SceneChanger = std::make_shared<Debug_SceneChanger>();
}

SceneBase::SceneBase(const std::string& name)
	:sceneName_(name)
{
	//debug_SceneChanger = std::make_shared<Debug_SceneChanger>();
}

void SceneBase::SceneInitialize()
{
	//rootObject_->SetTransform();
	//setter_ = ObjectSetter(rootObject_.get());
}

void SceneBase::SetRootObject(std::shared_ptr<Object> obj)
{
	rootObject_ = obj;
	rootObject_->Initialize();
}

std::shared_ptr<Object> SceneBase::GetRootObject()
{
	return rootObject_;
}

void SceneBase::ObjectSet()
{
	setter_.SetObject();
}

void SceneBase::SetFile(const std::string& name)
{
	fileName_ = name;
}

void SceneBase::Update()
{
//#ifdef _DEBUG
//	debug_SceneChanger->Update();
//#endif // DEBUG

	rootObject_->UpdateSub();
}

void SceneBase::StaticUpdate()
{
	rootObject_->StaticUpdateSub();
}

void SceneBase::CheckKillObject()
{
	rootObject_->ReleaseSub();
}

void SceneBase::Draw()
{
	rootObject_->DrawSub();
}

void SceneBase::AllKillObject()
{	
	rootObject_->KillAllChildren();
	setter_.DeleteObject();
}
