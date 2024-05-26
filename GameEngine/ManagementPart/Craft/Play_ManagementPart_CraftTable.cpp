#include "Play_ManagementPart_CraftTable.h"
#include"Play_ManagementPart_Manaita.h"
#include"Play_ManagementPart_Mortar.h"
#include"Play_ManagementPart_CraftPotModel.h"
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

	Play_ManagementPart_CraftPotModel* craftPot = Instantiate<Play_ManagementPart_CraftPotModel>(this);
	craftPot->GetTransform()->position_ = XMVectorSet(-1.5f, 3.25f, 1, 0);
	craftPot->GetTransform()->scale_ = { 0.7f,0.7f,0.7f };
	Play_ManagementPart_Manaita* manaita = Instantiate<Play_ManagementPart_Manaita>(this);
	manaita->GetTransform()->position_ = XMVectorSet(-4, 3.25f, 1, 0);
	Play_ManagementPart_Mortar* mortar = Instantiate<Play_ManagementPart_Mortar>(this);
	mortar->GetTransform()->position_ = XMVectorSet(-6.5f, 3.3f, 1,0);

}

void Play_ManagementPart_CraftTable::Update()
{
}

void Play_ManagementPart_CraftTable::Release()
{
}
