#pragma once
#include"SceneBase.h"
class Scene_Play_ManagementPart : public SceneBase
{
private:
public:
	Scene_Play_ManagementPart();
	Scene_Play_ManagementPart(const std::string& name);
	~Scene_Play_ManagementPart();
	void SceneInitialize() override;
};

