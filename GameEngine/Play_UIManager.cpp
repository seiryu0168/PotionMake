#include "Play_UIManager.h"
#include"Play_ManagementPart_BaseUI.h"
Play_UIManager::Play_UIManager(Object* parent)
	:GameObject(parent,"Play_UIManager")
{
}

Play_UIManager::~Play_UIManager()
{
}

void Play_UIManager::Initialize()
{
	if (GetSceneName() == "Play_ManagementPart")
	{
		Instantiate<Play_ManagementPart_BaseUI>(this);
	}
}

void Play_UIManager::Update()
{
}

void Play_UIManager::AccessUI(int uiNum)
{
	if (GetSceneName() == "Play_ManagementPart")
	{
		((Play_ManagementPart_BaseUI*)FindChild("Play_ManagementPart_BaseUI"))->AccessUI(uiNum);
	}
}

bool Play_UIManager::IsAccessUI()
{
	return ((Play_ManagementPart_BaseUI*)FindChild("Play_ManagementPart_BaseUI"))->IsAccessUI();
}

void Play_UIManager::Release()
{
}
