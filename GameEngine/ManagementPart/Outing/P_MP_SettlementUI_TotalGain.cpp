#include "P_MP_SettlementUI_TotalGain.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/ResourceManager/AudioManager.h"
P_MP_SettlementUI_TotalGain::P_MP_SettlementUI_TotalGain(Object* parent)
	:Window_Base(parent,"P_MP_SettlementUI_TotalGain"),
	uiPos_({ 0.2f,0.5f,0 }),
	gainDiff_(0.0f),
	showTime_(1.0f),
	currentGain_(0),
	hAudio_Money_(-1),
	count_(0),
	totalGain_(0)
{
}

P_MP_SettlementUI_TotalGain::~P_MP_SettlementUI_TotalGain()
{
}

void P_MP_SettlementUI_TotalGain::Initialize()
{
	CreateBase("Assets/Image/UIBaseImage4.png", uiPos_, {0.7f,0.3f},0.3f);
	CreateUITitle({ uiPos_.x - 0.23f,uiPos_.y+0.4f }, { 0,20 }, "îÑè„",55, { 102,100,82 });

	//çÄñ⁄ñºÇ∆ã‡äzÇ∆ï]âøÇÃÉeÉLÉXÉgèÄîı
	XMFLOAT3 txtPos = GetComponent<Image>().GetPositionAtPixel();
	//Text sectionText(this);
	//sectionText.SetText("îÑè„");
	//sectionText.SetRect({ 0,0,220,70 });
	//sectionText.SetPosition({ txtPos.x - 150,txtPos.y - 150 });
	//AddComponent<Text>(sectionText);

	Text totalGain(this);
	totalGain.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_TOP);
	totalGain.SetText("0");
	totalGain.SetRect({ 0,0,630,80 });
	totalGain.SetPosition({ txtPos.x - 450,txtPos.y-100 });
	AddComponent<Text>(totalGain);

	Text evaluation(this);
	evaluation.SetText("ëÂê∑ãµ");
	evaluation.SetPosition({ txtPos.x - 150,txtPos.y});
	AddComponent<Text>(evaluation);
	time_ = std::make_shared<Time::Watch>();
	time_->UnLock();

	hAudio_Money_ = AudioManager::Load("Assets/Audio/ShowMoney.wav",false,0.7f,10);
}

void P_MP_SettlementUI_TotalGain::Start()
{
}

void P_MP_SettlementUI_TotalGain::Update()
{
	float nowTime = time_->GetSeconds<float>();
	if (nowTime >= 0.7f && !time_->IsLock())
	{
		count_++;
		currentGain_ += gainDiff_;

		if(count_%8==0)
		AudioManager::Play(hAudio_Money_);
		GetComponent<Text>(1).SetText(std::to_string((int)currentGain_));
		if (currentGain_ >= totalGain_)
		{
			time_->Lock();
			GetComponent<Text>(1).SetText(std::to_string(totalGain_));
		}
	}
}

//void P_MP_SettlementUI_TotalGain::CreateBase()
//{
//	XMFLOAT3 windowSize;
//	XMFLOAT3 imageRatio;
//	Image uiBaseImage(this);
//	uiBaseImage.Load("Assets/Image/UIBaseImage4.png");
//	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
//	uiBaseImage.SetSize({ 16 * 0.7f,16 * 0.3f,0 });
//	windowSize = uiBaseImage.GetSizeAtPixel();
//	imageRatio = uiBaseImage.GetSize();
//	AddComponent<Image>(uiBaseImage);
//
//	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
//				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
//	Image uiWidthEdgeImage1(this);
//	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
//	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y,0 });
//	uiWidthEdgeImage1.SetSize({ imageRatio.x,0.3f,0 });
//	AddComponent<Image>(uiWidthEdgeImage1);
//	Image uiWidthEdgeImage2(this);
//	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
//	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y,0 });
//	uiWidthEdgeImage2.SetSize({ imageRatio.x,0.3f,0 });
//	AddComponent<Image>(uiWidthEdgeImage2);
//
//	Image uiHeightEdgeImage1(this);
//	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
//	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x,uiPos_.y,0 });
//	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y,0 });
//	AddComponent<Image>(uiHeightEdgeImage1);
//	Image uiHeightEdgeImage2(this);
//	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
//	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x,uiPos_.y,0 });
//	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y,0 });
//	AddComponent<Image>(uiHeightEdgeImage2);
//
//	Image uiCornerImage1(this);
//	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
//	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x,uiPos_.y + windowSize.y,0 });
//	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
//	AddComponent<Image>(uiCornerImage1);
//
//	Image uiCornerImage2(this);
//	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
//	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x,uiPos_.y - windowSize.y,0 });
//	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
//	uiCornerImage2.SetRotation({ 0,0,-90 });
//	AddComponent<Image>(uiCornerImage2);
//
//	Image uiCornerImage3(this);
//	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
//	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x,uiPos_.y - windowSize.y,0 });
//	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
//	uiCornerImage3.SetRotation({ 0,0,180 });
//	AddComponent<Image>(uiCornerImage3);
//
//	Image uiCornerImage4(this);
//	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
//	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x,uiPos_.y + windowSize.y,0 });
//	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
//	uiCornerImage4.SetRotation({ 0,0,90 });
//	AddComponent<Image>(uiCornerImage4);
//}

void P_MP_SettlementUI_TotalGain::SetData(int totalGain, const std::string& evaluation)
{
	totalGain_ = totalGain;
	evaluation_ = evaluation;
	gainDiff_ = totalGain / (showTime_ * 60.0f);
	//GetComponent<Text>(1).SetText(std::to_string(totalGain));
	//GetComponent<Text>(2).SetText(evaluation);
}
//void P_MP_SettlementUI_TotalGain::CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str)
//{
//	XMINT3 color = { 102,100,82 };
//	Text craftUIText(this);
//	craftUIText.SetText(str);
//	craftUIText.SetTextSize(55.0f);
//	float rectSize = craftUIText.GetTextSize() * str.size() * 0.5f;
//	TEXT_RECT rect = { 0,0,rectSize + diff.x,(float)craftUIText.GetTextSize() + diff.y };
//	XMFLOAT2 ratio = { 0.5f + (pos.x * 0.5f), 0.5f - (pos.y * 0.5f) };
//	ratio.x -= (rect.right / Direct3D::GetScreenWidth()) * 0.5f;
//	craftUIText.SetRect(rect);
//	craftUIText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
//	craftUIText.SetRatio(ratio.x, ratio.y);
//	AddComponent<Text>(craftUIText);
//
//	XMFLOAT2 imagePos = { pos.x ,pos.y - rect.bottom / Direct3D::GetScreenHeight() };
//	Image base(this);
//	base.Load("Assets/Image/UIBaseImage3.png");
//	base.SetSize({ 0.015625f * rect.right,0.015625f * rect.bottom,0 });
//	base.SetPosition({ imagePos.x,imagePos.y,0 });
//	base.SetColorInt(color);
//	XMFLOAT3 size = base.GetSizeAtPixel();
//	//XMFLOAT2 distance = { size.x / Direct3D::GetScreenWidth(),size.y / Direct3D::GetScreenHeight() };
//
//	float distance = rect.right / Direct3D::GetScreenWidth();
//	Image start(this);
//	start.Load("Assets/Image/UILong04_Start.png");
//	start.SetSize({ size.y / 256,size.y / 256,0.0f });
//	start.SetColorInt(color);
//	//start.SetRotation({ 0,0,180 });
//	start.SetPosition({ imagePos.x - distance - 0.03f,imagePos.y,0 });
//	AddComponent<Image>(start);
//
//	Image end(this);
//	end.Load("Assets/Image/UILong04_End.png");
//	end.SetSize({ size.y / 256,size.y / 256,0.0f });
//	end.SetColorInt(color);
//	end.SetPosition({ imagePos.x + distance + 0.03f,imagePos.y,0 });
//	AddComponent<Image>(end);
//
//	AddComponent<Image>(base);
//}

void P_MP_SettlementUI_TotalGain::Release()
{
}
