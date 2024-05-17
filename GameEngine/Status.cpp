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
	confirmation.SetSize({ 1.3f,1.3f,0 });
	statusImageNum_ = AddComponent<Image>(confirmation);

	PlayerData& pData = *InterSceneData::GetData<PlayerData>("Data01");

	XMFLOAT3 pos = confirmation.GetPositionAtPixel();
	XMFLOAT3 size = confirmation.GetSizeAtPixel();
	Text name(this);
	name.SetText("���O:"+pData.name_);
	name.SetPosition({ pos.x - size.x * 0.5f + 30,pos.y - size.y*0.4f });
	nameTextNum_ = AddComponent<Text>(name);

	Text  money(this);
	money.SetText("������:" + std::to_string(pData.money_));
	money.SetPosition({ pos.x - size.x * 0.5f + 30,pos.y - size.y * 0.4f + 100 });
	moneyTextNum_ = AddComponent<Text>(money);
	
	Text  craftCount(this);
	craftCount.SetText("�����:"+std::to_string(pData.craftCount_));
	craftCount.SetPosition({ pos.x - size.x * 0.5f + 30,pos.y - size.y * 0.4f+200 });
	moneyTextNum_ = AddComponent<Text>(craftCount);
	
	Text  sellCount(this);
	sellCount.SetText("�̔���:" + std::to_string(pData.sellCount_));
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
