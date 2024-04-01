#include "P_MP_CraftUI_ResourceStockUI.h"
#include"ResourceItem.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"InterSceneData.h"
#include"PlayerData.h"
P_MP_CraftUI_ResourceStockUI::P_MP_CraftUI_ResourceStockUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_ResourceStockUI"),
	uiPos_({0,0,0})
{
}

P_MP_CraftUI_ResourceStockUI::~P_MP_CraftUI_ResourceStockUI()
{
}

void P_MP_CraftUI_ResourceStockUI::Initialize()
{
	//UIの土台となる画像を用意
	uiPos_ = { 0.6,-0.13f,0 };
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition(uiPos_);
	uiBaseImage.SetSize({ 0.7f,0.87f,0 });
	AddComponent<Image>(uiBaseImage);

	//UIのカテゴリを表示
	Text uiTitleText(this);
	uiTitleText.SetText("素材");
	uiTitleText.SetPosition({ 1200,30 });
	AddComponent<Text>(uiTitleText);

	//素材の画像をセーブデータを参照して表示
	XMFLOAT2 itemPos = { -0.3f,0.68f };
	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	for (int i = 0; i < 30; i++)
	{
		//リソースオブジェクトの生成
		GameObject* item = Instantiate<ResourceItem>(this);


		int resourceCount = 0;
		if (i < data->itemDataList_.size())
			resourceCount = data->itemDataList_[i].itemCount_;

		((ResourceItem*)item)->LoadItem(data->itemDataList_[i % data->itemDataList_.size()].itemImageName_, resourceCount);
		item->GetComponent<Image>().SetPosition({ uiPos_.x + itemPos.x,uiPos_.y + itemPos.y,0 });
		if (resourceCount > 0)
		{
			((ResourceItem*)item)->itemName_ = data->itemDataList_[i % data->itemDataList_.size()].itemName_;

			item->GetComponent<Image>().SetSize({ 128.0f / 512.0f,128.0f / 521.0f,0 });
			XMFLOAT3 textBasePos = item->GetComponent<Image>().GetPositionAtPixel();
			item->GetComponent<Text>().SetPosition({ textBasePos.x+10,textBasePos.y });
		}

		itemPos.x += 0.15f;
		if ((i + 1) % 5 == 0)
		{
			itemPos.x = -0.3f;
			itemPos.y -= 0.27f;
		}
		((ResourceItem*)item)->SetItemNum(i);
	}
}

void P_MP_CraftUI_ResourceStockUI::Start()
{
}

void P_MP_CraftUI_ResourceStockUI::Update()
{
}

void P_MP_CraftUI_ResourceStockUI::Release()
{
}
