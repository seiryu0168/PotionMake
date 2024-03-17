#include"Scene_Play_ManagementPart.h"
#include"RootObject/RootObject_Play_ManagementPart.h"
Scene_Play_ManagementPart::Scene_Play_ManagementPart()
{
}

Scene_Play_ManagementPart::Scene_Play_ManagementPart(const std::string& name)
	:SceneBase(name)
{
}

Scene_Play_ManagementPart::~Scene_Play_ManagementPart()
{
}

void Scene_Play_ManagementPart::SceneInitialize()
{
	SetRootObject(std::make_shared<RootObject_Play_ManagementPart>());
}
