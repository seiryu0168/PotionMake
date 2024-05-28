#include "Play_UIManager.h"
#include"ManagementPart/Play_ManagementPart_BaseUI.h"
#include"CollectionPart/Play_CollectionPart_BaseUI.h"
#include"Engine/Systems/ImageSystem.h"
Play_UIManager::Play_UIManager(Object* parent)
	:GameObject(parent,"Play_UIManager"),
	accessUINum_(-1),
	time_(0)
{
}

Play_UIManager::~Play_UIManager()
{
}

void Play_UIManager::Initialize()
{
	//経営パートか採集パートかによって生成するベースUIを変える
	std::string sceneName = GetSceneName();
	if (sceneName == "Play_ManagementPart")
	{
		Instantiate<Play_ManagementPart_BaseUI>(this);
	}
	else if (sceneName == "Play_CollectionPart")
	{

		Instantiate<Play_CollectionPart_BaseUI>(this);
	}

	Image fadeImage(this);
	fadeImage.Load("Assets/Image/PotionManagerUIBase1.png");
	fadeImage.SetColor({ 0,0,0,0 });
	fadeImage.SetLayer(3);
	fadeImage.SetSize({ 2,2,0 });
	AddComponent<Image>(fadeImage);
}

void Play_UIManager::Update()
{
	if (time_ <= 0.5f)
	{
		time_ += 0.016;
		GetComponent<Image>().SetAlpha((0.5f-time_)/0.5f);
	}
}

void Play_UIManager::AccessUI(int uiNum)
{
	std::string sceneName = GetSceneName();
	if (sceneName == "Play_ManagementPart")
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
