#include "Player_ManagementPart.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/DirectX_11/Math.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/Systems/ColliderSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/GameObject/CameraManager.h"
#include"Play_UIManager.h"
#include"ManagementPartObjectBase.h"
#include"Play_ManagementPart_BaseUI.h"
#include"UIBase.h"
Player_ManagementPart::Player_ManagementPart(Object* parent)
	:Player(parent,"Player_ManagementPart")
{
}

Player_ManagementPart::~Player_ManagementPart()
{
}

void Player_ManagementPart::Initialize()
{
	HitBox collShape({ 2,2,2 });
	Collider coll({ 0,-5,0 });
	coll.SetCollider(collShape);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);

	Text noticeText(this);
	noticeText.SetText("Name");
	TEXT_RECT rect = { 0,0,1000,500 };
	noticeText.SetRect(rect);
	noticeText.SetColor({ 0,0,0,1 });
	AddComponent<Text>(noticeText);
	transform_->position_ = XMVectorSet(0, 10, 0, 0);
	CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
	CameraManager::GetCamera(0).SetTarget(XMVectorSet(0, 10, 1, 0));
}

void Player_ManagementPart::Start()
{
	SetUIManager(FindObject("Play_UIManager"));
}

void Player_ManagementPart::Update()
{
	if (((Play_UIManager*)GetUIManager())->IsAccessUI())
		return;
	MoveControll();


	CameraControll();


	//Š÷‚©’I‚©ƒhƒA‚É“–‚½‚Á‚Ä‚¢‚½‚ç
	if (GetComponent<Collider>().IsHit())
	{
		((Play_ManagementPart_BaseUI*)GetUIManager()->FindChild("Play_ManagementPart_BaseUI"))->DisplayAction(collisionObjectName_, true);//->GetComponent<Text>().SetText(collisionObjectName_);

		//((Play_ManagementPart_BaseUI*)UIManagerObject_->FindChild("Play_ManagementPart_BaseUI"))->SetUINum()
		//
		if (Input::IsKeyDown(DIK_F))
		{
			((Play_ManagementPart_BaseUI*)GetUIManager()->FindChild("Play_ManagementPart_BaseUI"))->AccessUI(collisionUINum_);
		}

	}
	else
		((Play_ManagementPart_BaseUI*)GetUIManager()->FindChild("Play_ManagementPart_BaseUI"))->DisplayAction("", false);
}

void Player_ManagementPart::Release()
{
}

void Player_ManagementPart::OnCollisionStay(GameObject* pTarget)
{
	collisionObjectName_ = ((ManagementPartObjectBase*)pTarget)->GetActionName();
	collisionUINum_ = ((ManagementPartObjectBase*)pTarget)->GetAccessUINumber();
}
