#pragma once
#include "SceneBase.h"
class Scene_Play : public SceneBase
{
public:
	Scene_Play();
	Scene_Play(const std::string& name);
	~Scene_Play();
	void SceneInitialize() override;
};

