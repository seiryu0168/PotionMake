#include "Scene_Play.h"
#include "RootObject/RootObject_Play.h"

Scene_Play::Scene_Play()
{
}

Scene_Play::Scene_Play(const std::string& name)
	: SceneBase(name)
{
}

Scene_Play::~Scene_Play()
{
}

void Scene_Play::SceneInitialize()
{
	SetRootObject(std::make_shared<RootObject_Play>());
}
