#include "Play_UIManager.h"
#include"Play_ManagementPart_BaseUI.h"
#include"Play_CollectionPart_BaseUI.h"
Play_UIManager::Play_UIManager(Object* parent)
	:GameObject(parent,"Play_UIManager"),
	accessUINum_(-1)
{
}

Play_UIManager::~Play_UIManager()
{
}

void Play_UIManager::Initialize()
{
	std::string sceneName = GetSceneName();
	if (sceneName == "Play_ManagementPart")
	{
		Instantiate<Play_ManagementPart_BaseUI>(this);
	}
	else if (sceneName == "Play_CollectionPart")
	{

		Instantiate<Play_CollectionPart_BaseUI>(this);
	}
}

void Play_UIManager::Update()
{
}

void Play_UIManager::AccessUI(int uiNum)
{
	std::string sceneName = GetSceneName();
	if (sceneName == "Play_ManagementPart")
	{
		((Play_ManagementPart_BaseUI*)FindChild("Play_ManagementPart_BaseUI"))->AccessUI(uiNum);
	}
	//else if (sceneName == "Play_CollectionPart")
	//{
	//	((Play_CollectionPart_BaseUI*)FindChild("Play_CollectionPart_BaseUI"))->
	//}

}

//GameObject* Play_UIManager::GetUI(std::string name)
//{
//	return (GameObject*)FindChild(name);
//}

bool Play_UIManager::IsAccessUI()
{
	return ((Play_ManagementPart_BaseUI*)FindChild("Play_ManagementPart_BaseUI"))->IsAccessUI();
}

void Play_UIManager::Release()
{
}
