#include "ResourceItem.h"
#include"../../Engine/DirectX_11/Input.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/Systems/TextSystem.h"
#include"P_MP_CraftUI_CraftPot.h"


ResourceItem::ResourceItem(Object* parent)
	:ItemBase(parent,"ResourceItem"),
	isLoadedImage_(false),
	resourceCount_(0), 
	resourceImageName_(""),
	textPos_({ 0,0 })
{
}

ResourceItem::~ResourceItem()
{
}

void ResourceItem::Initialize()
{
	Text countText(this);
	countText.SetLayer(1);
	countText.SetRect({ 0,0,50,50 });
	countText.SetTextSize(40);
	countText.SetText("0");
	countText.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_TOP);
	AddComponent<Text>(countText);
	//Image itemBaseImage(this);
	//itemBaseImage.Load("Assets/Image/ItemBaseImage.png");
	//AddComponent<Image>(itemBaseImage);
}

void ResourceItem::Start()
{
	potObject_ = (GameObject*)FindObject("P_MP_CraftUI_CraftPot");
}

void ResourceItem::Update()
{
	//画像をクリックしたら
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>().IsHitCursor())
	{
		//CraftPotにデータ反映
		if (resourceCount_ > 0)
		{
			((P_MP_CraftUI_CraftPot*)potObject_)->AddResourceData(itemNum_, itemName_, resourceImageName_);
			resourceCount_--;
			GetComponent<Text>().SetText(std::to_string(resourceCount_));
		}
	}
	else if (Input::IsMouseButtonDown(1) && GetComponent<Image>().IsHitCursor())
	{
		//CraftPotにデータ反映
		if (!((P_MP_CraftUI_CraftPot*)potObject_)->SubResourceData(itemNum_))
			return;
			resourceCount_++;
			GetComponent<Text>().SetText(std::to_string(resourceCount_));
	}
}

void ResourceItem::LoadItem(std::string imagename, int resourceCount)
{
	if (isLoadedImage_ == true)
		return;
	Image itemBaseImage(this);
	itemBaseImage.SetLayer(1);
	itemBaseImage.Load("Assets/Image/ItemBaseImage.png");
	resourceImageName_ = imagename;
	AddComponent<Image>(itemBaseImage);
	//素材の数が0以下だったら
	if (resourceCount <= 0)
	{
		GetComponent<Image>().SetColor(0.7f);
	}
	else
	{
		Image itemImage(this);
		itemImage.SetLayer(1);
		itemImage.Load("Assets/Image/" + imagename);
		itemImage.SetSize({ 0.25f,0.25f,0 });
		resourceImageName_ = imagename;
		AddComponent<Image>(itemImage);

	}
	

	//素材が0以上だったら
	if (resourceCount > 0)
	{

		resourceCount_ = resourceCount;
		GetComponent<Text>().SetText(std::to_string(resourceCount_));
	}
	isLoadedImage_ = true;
}

void ResourceItem::ActiveUI(bool isActive)
{
	GetComponent<Image>().SetDraw(isActive);
	GetComponent<Text>().isDraw_ = isActive;
}

void ResourceItem::Release()
{
}
