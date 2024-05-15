#include "ResourceItem.h"
#include "P_MP_CraftUI_CraftPot.h"
#include "../../Engine/DirectX_11/Input.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"


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
	//素材の数
	Text countText(this);
	countText.SetLayer(1);
	countText.SetRect({ 0,0,100,50 });
	countText.SetTextSize(32);
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
	if (!isLoadedImage_)
		return;

	//カーソルが画像に当たっていたら
	if (GetComponent<Image>().IsHitCursor())
	{
		GetComponent<Image>().SetColor(1.0f);
		//画像をクリックしたら
		if (Input::IsMouseButtonDown(0))
		{
			//CraftPotにデータ反映
			if (resourceCount_ > 0)
			{
				if (!((P_MP_CraftUI_CraftPot*)potObject_)->AddResourceData(itemNum_, itemName_, resourceImageName_))
					return;
				resourceCount_--;
				GetComponent<Text>().SetText(std::to_string(resourceCount_));
			}
		}
		else if (Input::IsMouseButtonDown(1))
		{
			//CraftPotにデータ反映
			if (!((P_MP_CraftUI_CraftPot*)potObject_)->SubResourceData(itemNum_))
				return;
			resourceCount_++;
			GetComponent<Text>().SetText(std::to_string(resourceCount_));
		}
	}
	else 
		GetComponent<Image>().SetColor(0.8f);
}

void ResourceItem::LoadItem(std::string imagename, int resourceCount)
{
	if (isLoadedImage_ == true)
		return;
	//ベースの画像
	Image itemBaseImage(this);
	itemBaseImage.SetLayer(1);
	itemBaseImage.Load("Assets/Image/ItemBaseImage.png");
	itemBaseImage.SetColor(0.8f);
	resourceImageName_ = imagename;
	AddComponent<Image>(itemBaseImage);

	//素材の数が0以下だったら
	if (resourceCount <= 0)
	{
		GetComponent<Image>().SetColor(0.7f);
	}
	else
	{
		//素材の画像
		Image itemImage(this);
		itemImage.SetLayer(1);
		itemImage.Load("Assets/Image/" + imagename);
		itemImage.SetSize({ 0.25f,0.25f,0 });
		resourceImageName_ = imagename;
		AddComponent<Image>(itemImage);
		isLoadedImage_ = true;

	}
	

	//素材が0以上だったら
	if (resourceCount > 0)
	{

		resourceCount_ = resourceCount;
		GetComponent<Text>().SetText(std::to_string(resourceCount_));
	}
}

void ResourceItem::ActiveUI(bool isActive)
{
	GetComponent<Image>().SetDraw(isActive);

	if(isLoadedImage_)
	GetComponent<Image>(1).SetDraw(isActive);

	GetComponent<Text>().isDraw_ = isActive;
}

void ResourceItem::Release()
{
}
