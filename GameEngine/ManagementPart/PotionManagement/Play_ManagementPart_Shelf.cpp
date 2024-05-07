#include "Play_ManagementPart_Shelf.h"
#include "../../Engine/Systems/ModelSystem.h"
#include "../../Engine/Systems/ColliderSystem.h"

Play_ManagementPart_Shelf::Play_ManagementPart_Shelf(Object* parent)
	:ManagementPartObjectBase(parent,"Play_ManagementPart_Shelf")
{
}

Play_ManagementPart_Shelf::~Play_ManagementPart_Shelf()
{
}

void Play_ManagementPart_Shelf::Initialize()
{
	accessUINum_ = 1;
	actionName_ = "ポーション管理";
	//当たり判定の設定
	HitBox tableHitBox({ 1,5,4 });
	Collider coll({ 0,5,-4 });
	coll.SetCollider(tableHitBox);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);
	
	//棚モデル
	Test_Model_ECSver shelf(this);
	shelf.Load("Assets/Model/bookcaseClosedWide.fbx");
	AddComponent<Test_Model_ECSver>(shelf);


	transform_->position_ = XMVectorSet(-19, 0, 0, 0);
	transform_->RotateEular(0, -90, 0);

}

void Play_ManagementPart_Shelf::Update()
{
}

void Play_ManagementPart_Shelf::Release()
{
}
