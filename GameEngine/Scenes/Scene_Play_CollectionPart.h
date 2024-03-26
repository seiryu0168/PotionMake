#pragma once
#include"SceneBase.h"
class Scene_Play_CollectionPart : public SceneBase
{
	Scene_Play_CollectionPart();
	Scene_Play_CollectionPart(const std::string& name);
	~Scene_Play_CollectionPart();
	void SceneInitialize() override;
};

