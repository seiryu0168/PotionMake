#include "Status.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"PlayerData.h"
namespace
{
	float TextSize = 60.0f;
}
Status::Status(Object* parent)
	:UIBase(parent,"Status")
{
}

Status::~Status()
{
}

void Status::Initialize()
{
	Image confirmation(this);
	confirmation.Load("Assets/Image/UIBaseImage1.png");
	confirmation.SetSize({ 1.3f,1.3f,0 });
	statusImageNum_ = AddComponent<Image>(confirmation);

	PlayerData& pData = *InterSceneData::GetData<PlayerData>("Data01");

	XMFLOAT3 pos = confirmation.GetPositionAtPixel();
	XMFLOAT3 size = confirmation.GetSizeAtPixel();
	Text name(this,"Rounded M+ 1c");
	name.SetText("ñºëO:"+pData.name_);
	name.SetTextSize(TextSize);
	name.SetPosition({ pos.x - size.x * 0.5f + 30,pos.y - size.y*0.4f });
	nameTextNum_ = AddComponent<Text>(name);

	Text  money(this, "Rounded M+ 1c");
	money.SetText("èäéùã‡:" + std::to_string(pData.money_));
	money.SetTextSize(TextSize);
	money.SetPosition({ pos.x - size.x * 0.5f + 30,pos.y - size.y * 0.4f + 100 });
	moneyTextNum_ = AddComponent<Text>(money);
	
	Text  craftCount(this, "Rounded M+ 1c");
	craftCount.SetText("êßçÏâÒêî:"+std::to_string(pData.craftCount_));
	craftCount.SetTextSize(TextSize);
	craftCount.SetPosition({ pos.x - size.x * 0.5f + 30,pos.y - size.y * 0.4f+200 });
	moneyTextNum_ = AddComponent<Text>(craftCount);
	
	Text  sellCount(this, "Rounded M+ 1c");
	sellCount.SetText("îÃîÑâÒêî:" + std::to_string(pData.sellCount_));
	sellCount.SetTextSize(TextSize);
	sellCount.SetPosition({ pos.x - size.x * 0.5f + 30,pos.y - size.y * 0.4f + 300 });
	moneyTextNum_ = AddComponent<Text>(sellCount);

}

void Status::Start()
{
}

void Status::Update()
{
}

void Status::Release()
{
}
