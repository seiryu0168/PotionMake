#include "Play_ManagementPart_PotionManagerUI.h"
#include "P_MP_PotionManagerUI_PotionStockUI.h"
#include "P_MP_PotionManagerUI_SellStockUI.h"
#include "P_MP_PotionManagerUI_DisposeStockUI.h"
#include "../Play_ManagementPart_BaseUI.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../CloseButton.h"
#include"../../TutorialButton.h"

Play_ManagementPart_PotionManagerUI::Play_ManagementPart_PotionManagerUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_PotionManagerUI")
{
}

Play_ManagementPart_PotionManagerUI::~Play_ManagementPart_PotionManagerUI()
{
}

void Play_ManagementPart_PotionManagerUI::Initialize()
{
	CreateUITitle({ 0,0.85f }, {10,30},"ポーション管理");

	//販売/破棄するポーションのUI
	Instantiate<P_MP_PotionManagerUI_SellStockUI>(this);
	Instantiate<P_MP_PotionManagerUI_DisposeStockUI>(this);
	Instantiate<P_MP_PotionManagerUI_PotionStockUI>(this);
	Instantiate<CloseButton>(this);

	TutorialButton* tutorialBtn = Instantiate<TutorialButton>(this);
	tutorialBtn->SetTutorialData("Assets/Image/Ico_Foot.png", "foot");
	tutorialBtn->SetTutorialData("Assets/Image/Icon_Luck.png", "luck");
	tutorialBtn->SetTutorialData("Assets/Image/Icon_Magic.png", "magic");
}

void Play_ManagementPart_PotionManagerUI::Update()
{
}

void Play_ManagementPart_PotionManagerUI::CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str)
{
	Text craftUIText(this);
	craftUIText.SetText(str);
	craftUIText.SetTextSize(70);
	float rectSize = craftUIText.GetTextSize() * str.size() * 0.5f;
	TEXT_RECT rect = { 0,0,rectSize + diff.x,(float)craftUIText.GetTextSize() + diff.y };
	XMFLOAT2 ratio = { 0.5f + (pos.x * 0.5f), 0.5f - (pos.y * 0.5f) };
	ratio.x -= (rect.right / Direct3D::GetScreenWidth()) * 0.5f;
	craftUIText.SetRect(rect);
	craftUIText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
	craftUIText.SetRatio(ratio.x, ratio.y);
	AddComponent<Text>(craftUIText);	

	XMFLOAT2 imagePos = { pos.x,pos.y - rect.bottom / Direct3D::GetScreenHeight() };
	Image base(this);
	base.Load("Assets/Image/UILong_Base.png");
	base.SetSize({ (1.0f / 256.0f) * rect.right,(1.0f / 256.0f) * rect.bottom,0 });
	base.SetPosition({ imagePos.x,imagePos.y,0 });
	XMFLOAT3 size = base.GetSizeAtPixel();
	//XMFLOAT2 distance = { size.x / Direct3D::GetScreenWidth(),size.y / Direct3D::GetScreenHeight() };

	float distance = (rect.right / Direct3D::GetScreenWidth());
	Image start(this);
	start.Load("Assets/Image/UILong_End.png");
	start.SetSize({ size.y / 256,size.y / 256,0.0f });
	start.SetRotation({ 0,0,180 });
	start.SetPosition({ imagePos.x - distance - 0.03f,imagePos.y,0 });
	AddComponent<Image>(start);

	Image end(this);
	end.Load("Assets/Image/UILong_End.png");
	end.SetSize({ size.y / 256,size.y / 256,0.0f });
	end.SetPosition({ imagePos.x + distance + 0.03f,imagePos.y,0 });
	AddComponent<Image>(end);

	//Text craftUIText(this);
	//craftUIText.SetText("素材");
	//craftUIText.SetRect({ 0,0,size.x,size.y });
	//craftUIText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
	//craftUIText.SetRatio(0.5f + ((pos.x - distance.x) * 0.5f), 0.5f - (pos.y * 0.5f) - (distance.y * 0.5f));
	//craftUIText.SetTextSize(70);


	AddComponent<Image>(base);
}

void Play_ManagementPart_PotionManagerUI::Release()
{
	Direct3D::ShowMouseCursor(false);
	XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	Direct3D::SetClipCursor({ rectPos.x,rectPos.y,rectPos.x + 1,rectPos.y + 1 });
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
