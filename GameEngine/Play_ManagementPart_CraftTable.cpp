#include "Play_ManagementPart_CraftTable.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/Systems/ColliderSystem.h"
Play_ManagementPart_CraftTable::Play_ManagementPart_CraftTable(Object* parent)
	:GameObject(parent,"Play_ManagementPart_CraftTable")
{
}

Play_ManagementPart_CraftTable::~Play_ManagementPart_CraftTable()
{
}

void Play_ManagementPart_CraftTable::Initialize()
{
	HitBox tableHitBox({ 1,1,2 });
	Collider coll({ 0,0,0 });
	coll.SetCollider(tableHitBox);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);

	Test_Model_ECSver tableModel(this);
	tableModel.Load("Assets/Model/tableCloth.fbx");
	AddComponent<Test_Model_ECSver>(tableModel);
	transform_->position_ = XMVectorSet(20, 0, 0,0);
	transform_->RotateEular(0, 90, 0);
}

void Play_ManagementPart_CraftTable::Update()
{
}

void Play_ManagementPart_CraftTable::Release()
{
}