#include "Scene_Result.h"
#include"RootObject/RootObject_Result.h"
Scene_Result::Scene_Result()
{
}

Scene_Result::Scene_Result(const std::string& name)
{
}

Scene_Result::~Scene_Result()
{
}

void Scene_Result::SceneInitialize()
{
	SetRootObject(std::make_shared<RootObject_Result>());
}
