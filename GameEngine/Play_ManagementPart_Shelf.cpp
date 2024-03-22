#include "Play_ManagementPart_Shelf.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/Systems/ColliderSystem.h"

Play_ManagementPart_Shelf::Play_ManagementPart_Shelf(Object* parent)
	:GameObject(parent,"Play_ManagementPart_Shelf")
{
}

Play_ManagementPart_Shelf::~Play_ManagementPart_Shelf()
{
}

void Play_ManagementPart_Shelf::Initialize()
{
	HitBox tableHitBox({ 5,5,1 });
	Collider coll({ -4,5,0 });
	coll.SetCollider(tableHitBox);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);

	Test_Model_ECSver tableModel(this);
	tableModel.Load("Assets/Model/bookcaseClosedWide.fbx");
	AddComponent<Test_Model_ECSver>(tableModel);


	transform_->position_ = XMVectorSet(0, 0, 20, 0);

}

void Play_ManagementPart_Shelf::Update()
{
}

void Play_ManagementPart_Shelf::Release()
{
}
