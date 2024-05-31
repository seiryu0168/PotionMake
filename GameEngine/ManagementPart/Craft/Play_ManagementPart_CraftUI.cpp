#include "Play_ManagementPart_CraftUI.h"
#include "P_MP_CraftUI_ResourceStockUI.h"
#include "P_MP_CraftUI_PotionStatusUI.h"
#include "P_MP_CraftUI_PrepareUI.h"
#include "PotionCraftAnimation.h"
#include "FinishCraftUI.h"
#include "../Play_ManagementPart_BaseUI.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../CloseButton.h"
#include"../../TutorialButton.h"
#include "../../Engine/DirectX_11/Input.h"
Play_ManagementPart_CraftUI::Play_ManagementPart_CraftUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_CraftUI")
{
}

Play_ManagementPart_CraftUI::~Play_ManagementPart_CraftUI()
{
}

void Play_ManagementPart_CraftUI::Initialize()
{
	//ポーション制作UIの題名
	//Text craftUIText(this);
	//craftUIText.SetText("ポーションを作る");
	//craftUIText.SetPosition({ 700,40 });
	//craftUIText.SetTextSize(70);
	//AddComponent<Text>(craftUIText);

	CreateUITitle({ 0.0f,0.9f },{10,30},"ポーション制作");

	Instantiate<P_MP_CraftUI_ResourceStockUI>(this);
	Instantiate<P_MP_CraftUI_PotionStatusUI>(this);
	Instantiate<P_MP_CraftUI_PrepareUI>(this);
	Instantiate<CloseButton>(this);
	TutorialButton* tutorialBtn = Instantiate<TutorialButton>(this);
	tutorialBtn->SetTutorialData("Assets/Image/Ico_Foot.png","foot");
	tutorialBtn->SetTutorialData("Assets/Image/Icon_Luck.png","luck");
	tutorialBtn->SetTutorialData("Assets/Image/Icon_Magic.png","magic");
	tutorialBtn->GetEnableFunction() = [&]() {return EnableUI(); };
	tutorialBtn->GetInvalidFunction() = [&]() {return InvalidUI(); };
	//for (int i = 0; i < 3; i++)
	//{
	//
	//}
}

void Play_ManagementPart_CraftUI::Update()
{
}

void Play_ManagementPart_CraftUI::DisplayCraftProcess(const std::vector<int>& itemNumList)
{
	//子供を全て殺してポーション制作のアニメーションを始める
	KillAllChildren();
	PotionCraftAnimation* potion = Instantiate<PotionCraftAnimation>(this);
	potion->InitAnimation(itemNumList);
}

void Play_ManagementPart_CraftUI::DisplayResult()
{
	//ポーション制作の結果表示
	FinishCraftUI* result = Instantiate<FinishCraftUI>(this);
}

void Play_ManagementPart_CraftUI::BeforeDeath()
{
}

void Play_ManagementPart_CraftUI::CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str)
{
	Text craftUIText(this);
	craftUIText.SetText(str);
	craftUIText.SetTextSize(70);
	float rectSize = craftUIText.GetTextSize() * str.size()*0.5f;
	TEXT_RECT rect = { 0,0,rectSize + diff.x,(float)craftUIText.GetTextSize() + diff.y };
	XMFLOAT2 ratio = { 0.5f + (pos.x * 0.5f), 0.5f - (pos.y * 0.5f) };
	ratio.x -= (rect.right / Direct3D::GetScreenWidth()) * 0.5f;
	craftUIText.SetRect(rect);
	craftUIText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
	craftUIText.SetRatio(ratio.x, ratio.y);
	AddComponent<Text>(craftUIText);

	XMFLOAT2 imagePos = {pos.x,pos.y - rect.bottom / Direct3D::GetScreenHeight() };
	Image base(this);
	base.Load("Assets/Image/UILong_Base.png");
	base.SetSize({ (1.0f/256.0f) * rect.right,(1.0f/256.0f) * rect.bottom,0 });
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

void Play_ManagementPart_CraftUI::EnableUI()
{
	FindChild("P_MP_CraftUI_ResourceStockUI")->SetUpdate(false);
	FindChild("P_MP_CraftUI_PotionStatusUI")->SetUpdate(false);
	FindChild("P_MP_CraftUI_PrepareUI")->SetUpdate(false);
}

void Play_ManagementPart_CraftUI::InvalidUI()
{
	FindChild("P_MP_CraftUI_ResourceStockUI")->SetUpdate(true);
	FindChild("P_MP_CraftUI_PotionStatusUI")->SetUpdate(true);
	FindChild("P_MP_CraftUI_PrepareUI")->SetUpdate(true);
}

void Play_ManagementPart_CraftUI::Release()
{
	Direct3D::ShowMouseCursor(false);
	XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	Direct3D::SetClipCursor({rectPos.x,rectPos.y,rectPos.x+1,rectPos.y+1});
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
