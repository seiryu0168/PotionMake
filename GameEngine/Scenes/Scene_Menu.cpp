#include "Scene_Menu.h"

Scene_Menu::Scene_Menu()
{
}

Scene_Menu::Scene_Menu(const std::string& name)
	:SceneBase(name)
{
}

Scene_Menu::~Scene_Menu()
{
}

void Scene_Menu::SceneInitialize()
{
	SetRootObject(std::make_shared<RootObject_Menu>());
}

//void Scene_Menu::AllKillObject()
//{
//	rootObject_->KillAllChildren();
//}
