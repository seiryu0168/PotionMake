#include "Play_ManagementPart_CraftTable.h"
#include "../../Engine/Systems/ModelSystem.h"
#include "../../Engine/Systems/ColliderSystem.h"
Play_ManagementPart_CraftTable::Play_ManagementPart_CraftTable(Object* parent)
	:ManagementPartObjectBase(parent,"Play_ManagementPart_CraftTable")
{
}

Play_ManagementPart_CraftTable::~Play_ManagementPart_CraftTable()
{
}

void Play_ManagementPart_CraftTable::Initialize()
{
	accessUINum_ = 2;
	actionName_ = "ポーションを作る";
	
	//当たり判定の設定
	HitBox tableHitBox({ 8,3,2 });
	Collider coll({ -8.5f,5,1 });
	coll.SetCollider(tableHitBox);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);

	//テーブルモデル
	Test_Model_ECSver tableModel(this);
	tableModel.Load("Assets/Model/tableCloth.fbx");
	AddComponent<Test_Model_ECSver>(tableModel);
	transform_->position_ = XMVectorSet(10, 0, 20,0);
	//transform_->RotateEular(0, 90, 0);
	transform_->scale_ = { 2,2,2 };
}

void Play_ManagementPart_CraftTable::Update()
{
}

void Play_ManagementPart_CraftTable::Release()
{
}
