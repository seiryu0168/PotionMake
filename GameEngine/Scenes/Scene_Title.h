#pragma once
#include"SceneBase.h"
#include"RootObject/RootObject_Title.h"
#include"../Debug_SceneChanger.h"
class Scene_Title : public SceneBase
{
public:
	Scene_Title();
	Scene_Title(const std::string& name);
	~Scene_Title();
	void SceneInitialize() override;
};

