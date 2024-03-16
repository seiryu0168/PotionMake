#pragma once
#include"../Engine/Coordinator.h"
#include"RootObject/RootObject.h"
#include"../ObjectSetter.h"
//#include"../Debug_SceneChanger.h"
class SceneBase
{
	std::shared_ptr<Object> rootObject_;
	//std::shared_ptr<Debug_SceneChanger> debug_SceneChanger;
	std::string sceneName_;
	std::string fileName_;
	ObjectSetter setter_;
public:
	SceneBase();
	SceneBase(const std::string& name);
	virtual ~SceneBase() {};
	virtual void SceneInitialize() = 0;
	void SetRootObject(std::shared_ptr<Object> obj);
	void ObjectSet();
	void SetFile(const std::string& name);
	void Update();
	void StaticUpdate();
	void CheckKillObject();
	void Draw();

	void AllKillObject();

};

