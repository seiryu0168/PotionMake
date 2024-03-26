#include "Scene_Play_CollectionPart.h"
#include"RootObject/RootObject_Play_CollectionPart.h"
Scene_Play_CollectionPart::Scene_Play_CollectionPart()
{
}

Scene_Play_CollectionPart::Scene_Play_CollectionPart(const std::string& name)
	:SceneBase(name)
{
}

Scene_Play_CollectionPart::~Scene_Play_CollectionPart()
{
}

void Scene_Play_CollectionPart::SceneInitialize()
{
	SetRootObject(std::make_shared<RootObject_Play_CollectionPart>());
}
