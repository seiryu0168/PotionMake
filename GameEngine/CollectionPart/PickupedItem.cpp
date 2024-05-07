#include "PickupedItem.h"
#include "P_CP_CollectedItemUI.h"
#include "PickupedItemDetailUI.h"
#include "../Engine/Systems/ImageSystem.h"
#include "../Engine/Systems/TextSystem.h"
#include "../Engine/DirectX_11/Input.h"
PickupedItem::PickupedItem(Object* parent)
	:ItemBase(parent,"PickupedItem"),
	itemCount_(0)
{
}

PickupedItem::~PickupedItem()
{
}

void PickupedItem::Initialize()
{
}

void PickupedItem::Start()
{
}

void PickupedItem::Update()
{
	if (Input::IsMouseButtonUp(0) && GetComponent<Image>().IsHitCursor()&&canSelect_)
	{
		Instantiate<PickupedItemDetailUI>(this)->SetItemData(itemNum_);
		((P_CP_CollectedItemUI*)pParent_)->SetSelectFlag(false);
	}
}

void PickupedItem::SetItemData(int itemNum, const std::string& itemName, int itemCount, const std::string& itemImageName, XMFLOAT3 pos)
{
	Image backImage(this);
	backImage.Load("Assets/Image/ItemBaseImage.png");
	backImage.SetPosition(pos);
	AddComponent<Image>(backImage);

	Image itemImage(this);
	itemImage.Load("Assets/Image/" + itemImageName);
	itemImage.SetPosition(pos);
	itemImage.SetSize({ 0.25f,0.25,0 });
	AddComponent<Image>(itemImage);

	XMFLOAT3 textPos = backImage.GetPositionAtPixel();
	Text countText(this);
	countText.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_TOP);
	countText.SetPosition({textPos.x,textPos.y});
	countText.SetRect({ 0,0,50,50 });
	countText.SetTextSize(40);
	countText.SetText(std::to_string(itemCount));
	AddComponent<Text>(countText);
	itemCount_ = itemCount;
	itemNum_ = itemNum;
	itemName_ = itemName;

}

void PickupedItem::Release()
{
}
