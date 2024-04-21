#include "P_CP_MenuUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"P_CP_CollectedItemUI.h"
#include"CloseButton.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"Engine/newSceneManager.h"
#include"PlayerData.h"
#include"ResourceStatusData.h"
#include"PickupedItem.h"
#include"Play_CollectionPart_BaseUI.h"
P_CP_MenuUI::P_CP_MenuUI(Object* parent)
	:GameObject(parent,"P_CP_MenuUI"),
	returnImageNum_(-1)
{
}

P_CP_MenuUI::~P_CP_MenuUI()
{
}

void P_CP_MenuUI::Initialize()
{
	Image returnHome(this);
	returnHome.Load("Assets/Image/SelectImage3.png");
	returnHome.SetPosition({ -1.2f,0.5f,0 });
	returnHome.SetRotation({ 0,0,180 });
	//returnHome.SetSize({ 5,2,0 });
	returnImageNum_ = AddComponent<Image>(returnHome);
	XMFLOAT3 textPos = GetComponent<Image>().GetPositionAtPixel();
	Text commandText(this);
	commandText.SetText("�Ƃɖ߂�");
	commandText.SetPosition({ textPos.x+200,textPos.y-50 });
	AddComponent<Text>(commandText);

	Instantiate<P_CP_CollectedItemUI>(this);

	GameObject* button = Instantiate<CloseButton>(this);
	button->GetComponent<Image>().SetPosition({ -0.9,0.9,0 });

}

void P_CP_MenuUI::Start()
{
}

void P_CP_MenuUI::Update()
{
	if (GetComponent<Image>(returnImageNum_).IsHitCursor())
	{
		GetComponent<Image>(returnImageNum_).SetPosition({ -1.1,0.5,0 });

		if (Input::IsMouseButtonUp(0))
		{
			SaveItemData();
			newSceneManager::ChangeScene(SCENE_ID::PLAY_MANAGEMENT);
		}

	}
	else
		GetComponent<Image>(returnImageNum_).SetPosition({ -1.2f,0.5f,0 });

}

void P_CP_MenuUI::SaveItemData()
{
	GameObject* itemUI = (GameObject*)FindChild("P_CP_CollectedItemUI");
	PlayerData* pData = InterSceneData::GetData<PlayerData>("Data01");
	ResourceStatusData* rData = InterSceneData::GetData<ResourceStatusData>("ResourceData");

	for (auto itr = itemUI->GetChildList()->begin();itr!=itemUI->GetChildList()->end();itr++)
	{
		PlayerData::ResourceData_ data;
		int num= ((PickupedItem*)itr->get())->GetItemNumber();
		data.itemNum_ = num;
		data.itemName_ = rData->resourceDataMap_[num].resourceName_;
		data.itemImageName_ = rData->resourceDataMap_[num].resourceImageName_;
		data.itemCount_= ((PickupedItem*)itr->get())->GetItemCount();
		pData->AddResourceItemData(data);
	}

}

void P_CP_MenuUI::Release()
{
	((Play_CollectionPart_BaseUI*)pParent_)->SetUIOpenFlag(false);
}
