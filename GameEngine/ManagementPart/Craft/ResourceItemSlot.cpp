#include "ResourceItemSlot.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/Systems/TextSystem.h"
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
	slotImage.Load("Assets/Image/ItemBaseImage.png");
	slotImage.SetColor(0.7f);
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

void ResourceItemSlot::SetItem(const std::string& resourceName, const std::string& imageName,int itemNum)
{
	//îwåiÇñæÇÈÇ≠Ç∑ÇÈ
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	GetComponent<Image>().SetColor(1);
	//RemoveComponent<Image>();

	//ëfçﬁÇÃâÊëúÇê›íË
	Image slotImage(this);
	slotImage.Load("Assets/Image/"+ imageName);
	XMFLOAT3 size = slotImage.GetOriginalImageSize();
	slotImage.SetSize({ 128.0f / size.x,128.0f / size.y,0 });
	slotImage.SetPosition(pos);
	AddComponent<Image>(slotImage);

	haveResource_ = true;
	resourceCount_++;
	GetComponent<Text>().SetText(std::to_string(resourceCount_));
	itemNum_ = itemNum;
	itemName_ = resourceName;
}

void ResourceItemSlot::ItemEmpty()
{
	//îwåiÇà√Ç≠ÇµÅAëfçﬁÇÃâÊëúÇè¡Ç∑
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	GetComponent<Image>().SetColor(0.7f);

	RemoveComponent<Image>(1);

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
