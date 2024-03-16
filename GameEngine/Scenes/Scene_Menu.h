#pragma once
#include"SceneBase.h"
#include"RootObject/RootObject_Menu.h"
class Scene_Menu : public SceneBase
{
	//std::shared_ptr<RootObject_Menu> rootObject_;
public:
	Scene_Menu();
	Scene_Menu(const std::string& name);
	~Scene_Menu();
	void SceneInitialize() override;
};

