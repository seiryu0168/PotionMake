#include "PickupedItemDetailUI.h"
#include "P_CP_CollectedItemUI.h"
#include "../Engine/Systems/ImageSystem.h"
#include "../Engine/Systems/TextSystem.h"
#include "../CloseButton.h"
#include "../InterSceneData.h"
#include "../ResourceStatusData.h"
#include "../Engine/ResourceManager/Audio.h"
PickupedItemDetailUI::PickupedItemDetailUI(Object* parent)
	:GameObject(parent, "PickupedItemDetailUI"),
	uiPos_({ -0.2f,0,0 }),
	hAudio_OpenUI_(-1)
{
}

PickupedItemDetailUI::~PickupedItemDetailUI()
{
}

void PickupedItemDetailUI::Initialize()
{
	//îwåiâÊëú
	Image backImage(this);
	backImage.Load("Assets/Image/UIBaseImage4.png");
	backImage.SetPosition(uiPos_);
	backImage.SetSize({ 6,10,0 });
	AddComponent<Image>(backImage);
	GameObject* button = Instantiate<CloseButton>(this);
	button->GetComponent<Image>().SetPosition({ -0.4,0.55,0 });

	hAudio_OpenUI_ = Audio::Load("Assets/Audio/Confirm34.wav");
	Audio::Play(hAudio_OpenUI_);
}

void PickupedItemDetailUI::Start()
{
}

void PickupedItemDetailUI::Update()
{
}

void PickupedItemDetailUI::SetItemData(int itemNum)
{
	//ÉäÉ\Å[ÉXÉfÅ[É^éÊìæ
	ResourceStatusData* rData = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	
	//ëfçﬁÇÃâÊëú
	Image itemImage(this);
	itemImage.Load("Assets/Image/"+rData->resourceDataMap_[itemNum].resourceImageName_);
	itemImage.SetSize({ 0.5f,0.5f,0 });
	itemImage.SetPosition({ uiPos_.x,uiPos_.y + 0.2f,0 });
	AddComponent<Image>(itemImage);

	XMFLOAT3 textPos = itemImage.GetPositionAtPixel();
	
	//ëfçﬁñº
	Text itemNameText(this);
	itemNameText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	itemNameText.SetTextSize(50);
	itemNameText.SetRect({ 0,0,300,60 });
	itemNameText.SetText(rData->resourceDataMap_[itemNum].resourceName_);
	itemNameText.SetPosition({ textPos.x - 150,textPos.y+105 });
	AddComponent<Text>(itemNameText);
	
	//ëfçﬁÇÃê‡ñæ
	Text itemDetailText(this);
	itemDetailText.SetText(rData->resourceDataMap_[itemNum].explanation_);
	itemDetailText.SetRect({ 0,0,300,240 });
	itemDetailText.SetTextSize(25);
	itemDetailText.SetPosition({ textPos.x - 150,textPos.y + 170 });
	AddComponent<Text>(itemDetailText);
}

void PickupedItemDetailUI::Release()
{
	((P_CP_CollectedItemUI*)pParent_->GetParent())->SetSelectFlag(true);
}
