#pragma once
#include"SceneBase.h"
class Scene_Result : public SceneBase
{
public:
	Scene_Result();
	Scene_Result(const std::string& name);
	~Scene_Result();

	void SceneInitialize() override;
};

