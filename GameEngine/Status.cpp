#include "Status.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"PlayerData.h"
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
	statusImageNum_ = AddComponent<Image>(confirmation);

	PlayerData& pData = *InterSceneData::GetData<PlayerData>("Data01");

	XMFLOAT3 pos = confirmation.GetPositionAtPixel();
	Text name(this);
	name.SetText(pData.name_);
	name.SetPosition({ pos.x - 200,pos.y - 200 });
	nameTextNum_ = AddComponent<Text>(name);

	Text  money(this);
	money.SetText(std::to_string(pData.money_));
	money.SetPosition({ pos.x - 200,pos.y - 100 });
	moneyTextNum_ = AddComponent<Text>(money);
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
