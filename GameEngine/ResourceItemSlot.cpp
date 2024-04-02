#include "ResourceItemSlot.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
ResourceItemSlot::ResourceItemSlot(Object* parent)
	:ItemBase(parent,"ResourceItemSlot"),
	haveResource_(false),
	resourceCount_(0)
{
}

ResourceItemSlot::~ResourceItemSlot()
{
}

void ResourceItemSlot::Initialize()
{
	Image slotImage(this);
	slotImage.Load("Assets/Image/ItemSlotImage.png");
	AddComponent<Image>(slotImage);

	Text countText(this);
	countText.SetRect({ 0,0,50,50 });
	countText.SetTextSize(40);
	countText.SetText("0");
	countText.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_TOP);
	AddComponent<Text>(countText);
	//haveResource_ = true;

}

void ResourceItemSlot::Start()
{
}

void ResourceItemSlot::Update()
{
}

void ResourceItemSlot::SetItem(std::string imageName,int itemNum)
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();

	RemoveComponent<Image>();

	Image slotImage(this);
	slotImage.Load("Assets/Image/"+ imageName);
	XMFLOAT3 size = slotImage.GetSizeAtPixel();
	slotImage.SetSize({ 128.0f / size.x,128.0f / size.y,0 });
	slotImage.SetPosition(pos);
	AddComponent<Image>(slotImage);

	haveResource_ = true;
	resourceCount_++;
	GetComponent<Text>().SetText(std::to_string(resourceCount_));
	itemNum_ = itemNum;
}

void ResourceItemSlot::ItemEmpty()
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();

	RemoveComponent<Image>();

	Image slotImage(this);
	slotImage.Load("Assets/Image/ItemSlotImage.png");
	XMFLOAT3 size = slotImage.GetSizeAtPixel();
	slotImage.SetSize({ 128.0f / size.x,128.0f / size.y,0 });
	slotImage.SetPosition(pos);
	AddComponent<Image>(slotImage);
	haveResource_ = false;
	resourceCount_ = 0;
	GetComponent<Text>().SetText(std::to_string(resourceCount_));
	itemNum_ = -1;
}

void ResourceItemSlot::AddCount(int increase)
{
	 resourceCount_ += increase;
	 GetComponent<Text>().SetText(std::to_string(resourceCount_));
}

void ResourceItemSlot::SubCount(int subtract)
{
	 resourceCount_ -= subtract;
	 GetComponent<Text>().SetText(std::to_string(resourceCount_));
}

void ResourceItemSlot::Release()
{
}
