#include "Play_CollectionPart_BaseUI.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/Systems/ImageSystem.h"
#include"InterSceneData.h"

Play_CollectionPart_BaseUI::Play_CollectionPart_BaseUI(Object* parent)
	:GameObject(parent,"Play_CollectionPart_BaseUI")
{
}

Play_CollectionPart_BaseUI::~Play_CollectionPart_BaseUI()
{
}

void Play_CollectionPart_BaseUI::Initialize()
{
	itemName_.push_back("Item1");
	itemName_.push_back("Item2");
	itemName_.push_back("Item3");
	itemName_.push_back("Item4	");
	Image actionImage(this);
	actionImage.Load("Assets/Image/SelectImage3.png");
	actionImage.SetPosition({ 0.7f,-0.015f,0 });
	actionImage.SetSize({ 0.7,0.7f,0 });
	AddComponent<Image>(actionImage);

	Text itemNameText(this);
	itemNameText.SetText("");
	itemNameText.SetRect({ 0,0,500,500 });
	itemNameText.SetPosition({ 1320,500 });
	AddComponent<Text>(itemNameText);
}

void Play_CollectionPart_BaseUI::Start()
{
}

void Play_CollectionPart_BaseUI::Update()
{
}

void Play_CollectionPart_BaseUI::DisplayItemName(int itemNum)
{	
	GetComponent<Image>().SetDraw(true);
	GetComponent<Text>().SetText(itemName_[itemNum]);
	GetComponent<Text>().isDraw_ = true;
}

void Play_CollectionPart_BaseUI::HiddenItemName()
{
	GetComponent<Image>().SetDraw(false);
	GetComponent<Text>().isDraw_=false;
}

void Play_CollectionPart_BaseUI::Release()
{
}
