#include "ResourceItemSlot.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
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
	//�f�ޕ\���̘g�摜
	Image slotImage(this);
	slotImage.Load("Assets/Image/ItemBaseImage.png");
	slotImage.SetColor(0.7f);
	AddComponent<Image>(slotImage);

	//�f�ނ̐�
	Text countText(this, "Rounded M+ 1c");
	countText.SetRect({ 0,0,50,50 });
	countText.SetTextSize(32);
	countText.SetText("");
	countText.isDraw_ = false;
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
	//�w�i�𖾂邭����
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	GetComponent<Image>().SetColor(1);
	//RemoveComponent<Image>();

	//�f�ނ̉摜��ݒ�
	Image slotImage(this);
	slotImage.Load("Assets/Image/"+ imageName);
	XMFLOAT3 size = slotImage.GetOriginalImageSize();
	slotImage.SetSize({ 128.0f / size.x,128.0f / size.y,0 });
	slotImage.SetPosition(pos);
	AddComponent<Image>(slotImage);

	haveResource_ = true;
	resourceCount_++;
	GetComponent<Text>().isDraw_ = true;
	GetComponent<Text>().SetText(std::to_string(resourceCount_));
	itemNum_ = itemNum;
	itemName_ = resourceName;
}

void ResourceItemSlot::ItemEmpty()
{
	//�w�i���Â����A�f�ނ̉摜������
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	GetComponent<Image>().SetColor(0.7f);

	RemoveComponent<Image>(1);

	haveResource_ = false;
	resourceCount_ = 0;
	GetComponent<Text>().isDraw_ = false;
	itemNum_ = -1;
}

void ResourceItemSlot::AddCount(int increase)
{
	 resourceCount_ += increase;
	 GetComponent<Text>().isDraw_ = true;
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
