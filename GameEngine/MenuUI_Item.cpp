#include "MenuUI_Item.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"PlayerData.h"
#include"ResourceStatusData.h"
#include"CollectionPart/P_CP_CollectedItemUI.h"
#include"CloseButton.h"
#include"Engine/Components/Audio.h"
MenuUI_Item::MenuUI_Item(Object* parent)
	:UIBase(parent,"MenuUI_Item"),
	isClickedButton_(false)
{
}

MenuUI_Item::~MenuUI_Item()
{
}

void MenuUI_Item::Initialize()
{
	Image save(this);
	save.Load("Assets/Image/SelectImage3.png");
	save.SetPosition({ -1.2f,-0.5f,0 });
	save.SetRotation({ 0,0,180 });
	//save.SetSize({ 5,2,0 });
	AddComponent<Image>(save);
	XMFLOAT3 textPos = save.GetPositionAtPixel();
	Text saveText(this);
	saveText.SetText("セーブ");
	saveText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(saveText);
}

void MenuUI_Item::Start()
{
}

void MenuUI_Item::Update()
{
	if (!isClickedButton_)
	{
		//他のUIを開いてる場合
		if (((UIBase*)pParent_)->GetCurrentOpenUINumber() != -1)
			return;
		if (!GetComponent<Image>().IsHitCursor())
		{
			GetComponent<Image>().SetPosition({ -1.2f,-0.5f,0 });
			return;
		}
		GetComponent<Image>().SetPosition({ -1.1,-0.5,0 });
		if (Input::IsMouseButtonUp(0) && GetComponent<Image>().IsHitCursor() && !isClickedButton_)
		{
			isClickedButton_ = true;
			pParent_->GetComponent<Audio>().Play();
			CretateItemList();
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			//SetDrawFlag(true);
			GetComponent<Image>().SetPosition({ -1.2f,-0.5f,0 });
		}

	}
}

void MenuUI_Item::CretateItemList()
{
	P_CP_CollectedItemUI& collectedUI = *Instantiate<P_CP_CollectedItemUI>(this);
	ResourceStatusData& rData = *InterSceneData::GetData<ResourceStatusData>("ResourceData");
	//PlayerData::ResourceData_ prData = InterSceneData::GetData<PlayerData>("Data01")->itemDataList_;
	for (auto& itr : InterSceneData::GetData<PlayerData>("Data01")->itemDataList_)
	{
		collectedUI.SetItemData(itr.itemNum_,
			rData.resourceDataMap_[itr.itemNum_].resourceName_,
			itr.itemCount_,
			rData.resourceDataMap_[itr.itemNum_].resourceImageName_);
	}

	collectedUI.SetDummy();

	CloseButton& clsBtn = *Instantiate<CloseButton>(&collectedUI);
	clsBtn.GetComponent<Image>().SetPosition({ 0,0.7f,0 });
	clsBtn.GetFunction() = [&]() {return ClickCloseButton(); };
}

void MenuUI_Item::ClickCloseButton()
{
	((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
	isClickedButton_ = false;
}

void MenuUI_Item::Release()
{
}
