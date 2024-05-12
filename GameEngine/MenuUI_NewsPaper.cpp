#include "MenuUI_NewsPaper.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"PlayerData.h"
#include"ResourceStatusData.h"
MenuUI_NewsPaper::MenuUI_NewsPaper(Object* parent)
	:UIBase(parent,"MenuUI_NewsPaper"),
	isClickedButton_(false),
	closeButtonNum_(-1)
{
}

MenuUI_NewsPaper::~MenuUI_NewsPaper()
{
}

void MenuUI_NewsPaper::Initialize()
{
	Image buttonImage(this);
	buttonImage.Load("Assets/Image/SelectImage3.png");
	buttonImage.SetPosition({ -1.2f,0.2f,0 });
	buttonImage.SetRotation({ 0,0,180 });
	AddComponent<Image>(buttonImage);

	XMFLOAT3 textPos = buttonImage.GetPositionAtPixel();
	Text buttonText(this);
	buttonText.SetText("êVï∑");
	buttonText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(buttonText);
	
	int num = InterSceneData::GetData<PlayerData>("Data01")->newsPaperNumber_;
	std::string imageName = InterSceneData::GetData<ResourceStatusData>("ResourceData")->newsPaperList_[num].resourceImageName_;
	Image newsPaperImage(this);
	newsPaperImage.Load("Assets/Image/" + imageName);
	newsPaperImage.SetPosition({ 0.4f,0,0 });
	newsPaperImage.SetDraw(false);
	AddComponent<Image>(newsPaperImage);

	Image closeImage(this);
	closeImage.Load("Assets/Image/CloseButtonImage.png");
	closeImage.SetPosition({ 0,0.5f,0 });
	closeImage.SetSize({ 0.6f,0.6f,0 });
	closeImage.SetDraw(false);
	closeButtonNum_ = AddComponent<Image>(closeImage);
}

void MenuUI_NewsPaper::Start()
{
}

void MenuUI_NewsPaper::Update()
{
	if (isClickedButton_)
	{
		if (Input::IsMouseButtonUp(0))
		{
			if (GetComponent<Image>(closeButtonNum_).IsHitCursor())
			{
				((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
				isClickedButton_ = false;
				SetDrawFlag(false);
			}
		}
	}

	if (!isClickedButton_)
	{
		//ëºÇÃUIÇäJÇ¢ÇƒÇÈèÍçá
		if (((UIBase*)pParent_)->GetCurrentOpenUINumber() != -1)
			return;

		if (!GetComponent<Image>().IsHitCursor())
		{
			GetComponent<Image>().SetPosition({ -1.2f,0.2f,0 });
			return;
		}
		GetComponent<Image>().SetPosition({ -1.1f,0.2f,0 });
		if (Input::IsMouseButtonUp(0) && GetComponent<Image>().IsHitCursor() && !isClickedButton_)
		{
			isClickedButton_ = true;
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			SetDrawFlag(true);
			GetComponent<Image>().SetPosition({ -1.2f,0.2f,0 });
		}

	}
}

void MenuUI_NewsPaper::SetDrawFlag(bool flag)
{
	GetComponent<Image>(1).SetDraw(flag);
	GetComponent<Image>(closeButtonNum_).SetDraw(flag);
}

void MenuUI_NewsPaper::Release()
{
}
