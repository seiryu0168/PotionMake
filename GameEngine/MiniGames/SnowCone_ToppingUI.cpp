#include "SnowCone_ToppingUI.h"
#include"../Engine/Systems/ImageSystem.h"
#include"../Engine/Systems/TextSystem.h"
#include"SnowCone_SyrupSelect.h"
#include"SnowCone_ToppingSelect.h"

namespace
{
	const XMFLOAT2 COMMANDTEXT_POS[] = { { 150,850 },{ 1150,850 } ,{ 1050,850 }, { 1450,850 },{ 1050,900 },{ 1450,900 } };
	const XMFLOAT3 COMMANDIMAGE_POS[] = { {-1700,-675,0},{-1700,-700,0},{100,-675,0} };
	
}

SnowCone_ToppingUI::SnowCone_ToppingUI(Object* parent)
	:GameObject(parent,"SnowCone_ToppingUI"),
	syrupSelect_(nullptr),
	toppingSelect_(nullptr),
	mode_(SELECT_MODE::MODE_SYRUP)
{
}

SnowCone_ToppingUI::~SnowCone_ToppingUI()
{
}

void SnowCone_ToppingUI::Initialize()
{
	
	//プレイヤー1の手順
	{
		std::string str = "手順\n1.かき氷を用意する  2.かき氷を削る\n3.かき氷を渡す";
		Text text("", "りいてがき筆", { 0,0,1000,200 });
		text.SetText(str);
		text.SetColor({ 0,0,0,1 });
		text.SetPosition(COMMANDTEXT_POS[0]);
		text.SetTextSize(40);
		text.SetTextSize(60,0,2);
		AddComponent<Text>(text);
	}
	//プレイヤー2の手順
	{
		std::string str = "手順\n1.かき氷を受け取る  2.シロップを選ぶ\n3.トッピングを選ぶ  4.かき氷を出す";
		Text text("", "りいてがき筆", { 0,0,1000,200 });
		text.SetText(str);
		text.SetColor({ 0,0,0,1 });
		text.SetPosition(COMMANDTEXT_POS[1]);
		text.SetTextSize(40);
		text.SetTextSize(60,0,2);
		AddComponent<Text>(text);
	}
	
	//シロップとトッピングを選ぶUIの生成
	toppingSelect_ = Instantiate<SnowCone_ToppingSelect>(this);
	syrupSelect_ = Instantiate<SnowCone_SyrupSelect>(this);
	toppingSelect_->SetUpdate(false);

}

void SnowCone_ToppingUI::Update()
{

}

int SnowCone_ToppingUI::GetSyrupData()
{
	return syrupSelect_->GetSyrupNum();
}

int SnowCone_ToppingUI::GetToppingData()
{
	return toppingSelect_->GetToppingNum();
}

Image SnowCone_ToppingUI::GetCurrentSyrupImage()
{
	return GetComponent<Image>(GetSyrupData());
}

Image SnowCone_ToppingUI::GetCurrentToppingImage()
{
	return GetComponent<Image>(GetToppingData());
}

void SnowCone_ToppingUI::ModeChange(SELECT_MODE mode)
{
	switch (mode)
	{
	case SELECT_MODE::MODE_SYRUP:
		syrupSelect_->SetUpdate(true);
		toppingSelect_->SetUpdate(false);
		break;
	case SELECT_MODE::MODE_TOPPING:
		syrupSelect_->SetUpdate(false);
		toppingSelect_->SetUpdate(true);
		break;
	case SELECT_MODE::MODE_COMPLETE:
		syrupSelect_->SetUpdate(false);
		toppingSelect_->SetUpdate(false);
		break;
	default:
		break;
	}
}

void SnowCone_ToppingUI::ResetUI()
{
	syrupSelect_->UIReset();
	toppingSelect_->UIReset();
	ModeChange(SELECT_MODE::MODE_SYRUP);
}

void SnowCone_ToppingUI::Release()
{
}
