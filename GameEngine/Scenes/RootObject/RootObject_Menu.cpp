#include "RootObject_Menu.h"
#include"../../Engine/Components/Transform.h"
#include"../../StaticResource.h"
#include"../../MainMenu.h"

RootObject_Menu::RootObject_Menu()
{
	Transform transform;
	AddComponent<Transform>(transform);
}

RootObject_Menu::~RootObject_Menu()
{
}

void RootObject_Menu::Initialize()
{
	Instantiate<MainMenu>(this);
	
}

void RootObject_Menu::Release()
{
}
