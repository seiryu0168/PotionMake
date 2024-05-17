#include "PickupedItem.h"
#include "P_CP_CollectedItemUI.h"
#include "PickupedItemDetailUI.h"
#include "../Engine/Systems/ImageSystem.h"
#include "../Engine/Systems/TextSystem.h"
#include "../Engine/DirectX_11/Input.h"
PickupedItem::PickupedItem(Object* parent)
	:ItemBase(parent,"PickupedItem"),
	itemCount_(0),
	canSelect_(true)
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
	if (GetComponent<Image>().IsHitCursor() && canSelect_)
	{

		GetComponent<Image>().SetColor(1.0f);
		if (Input::IsMouseButtonUp(0)&& canSelect_)
		{
			//ëfçﬁÇÃè⁄ç◊
			Instantiate<PickupedItemDetailUI>(this)->SetItemData(itemNum_);
			((P_CP_CollectedItemUI*)pParent_)->SetSelectFlag(false);
		}
	}
	else
		GetComponent<Image>().SetColor(0.8f);
}

void PickupedItem::SetItemData(int itemNum, const std::string& itemName, int itemCount, const std::string& itemImageName, XMFLOAT3 pos)
{
	//UIÇÃÉxÅ[ÉXâÊëú
	Image backImage(this);
	backImage.Load("Assets/Image/ItemBaseImage.png");
	backImage.SetPosition(pos);
	backImage.SetColor(0.8f);
	AddComponent<Image>(backImage);

	//ëfçﬁÇÃâÊëú
	Image itemImage(this);
	itemImage.Load("Assets/Image/" + itemImageName);
	itemImage.SetPosition(pos);
	itemImage.SetSize({ 0.25f,0.25,0 });
	AddComponent<Image>(itemImage);

	XMFLOAT3 textPos = backImage.GetPositionAtPixel();
	//ëfçﬁÇÃêî
	Text countText(this);
	countText.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_TOP);
	countText.SetPosition({textPos.x-40,textPos.y+30});
	countText.SetRect({ 0,0,100,50 });
	countText.SetTextSize(33);
	countText.SetText(std::to_string(itemCount));
	AddComponent<Text>(countText);
	itemCount_ = itemCount;
	itemNum_ = itemNum;
	itemName_ = itemName;

}

void PickupedItem::Release()
{
}
