#include "Select_StaticUI.h"
#include "Engine/DirectX_11/Math.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"

#include "Engine/ResourceManager/Audio.h"

namespace
{
	static const int Period = 3840;
}

Select_StaticUI::Select_StaticUI(Object* parent)
	:GameObject(parent,"Select_StaticUI"), Frame_(0), backGroundImageList_(), hAudio_(-1)
{
}

Select_StaticUI::~Select_StaticUI()
{
}

void Select_StaticUI::Initialize()
{
	//プレイヤーが動かす必要のない文字や画像を生成
	Text selectText("ゲームセレクト","りいてがき筆",{0,0,900,50});
	selectText.SetTextSize(100);
	selectText.SetRatio(0.3f, 0.05f);
	//selectText.SetPosition({610,0});
	AddComponent<Text>(selectText);

	{
		Image i;
		i.Load("Assets/Image/BG_fes.png", "Select_Static");
		int I = AddComponent(i);
		backGroundImageList_.push_back(&GetComponent<Image>(I));
	}

	//ならない
	hAudio_ = Audio::Load("Assets\\Audio\\menu.wav");
	
}

void Select_StaticUI::Update()
{
	//スクロール
	float Ratio = ++Frame_ / (float)Period;
	float sin = Math::Sincurve(Ratio);
	for (auto&& itr : backGroundImageList_)
	{
		itr->SetScroll({ Ratio, sin });
	}

	Audio::Play(hAudio_);
}

void Select_StaticUI::Release()
{
}
