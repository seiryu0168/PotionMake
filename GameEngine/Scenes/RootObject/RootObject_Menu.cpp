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

	//AddComponent<Image>(StaticResource::GetImage("image01"));
	//Instantiate<Select_StaticUI>(this);
	//Instantiate<SelectUI>(this);
	Instantiate<MainMenu>(this);
	
}

void RootObject_Menu::Release()
{
}
