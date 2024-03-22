#include "Play_ManagementPart_Door.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/Systems/ColliderSystem.h"

Play_ManagementPart_Door::Play_ManagementPart_Door(Object* parent)
	:GameObject(parent,"Play_ManagementPart_Door")
{
}

Play_ManagementPart_Door::~Play_ManagementPart_Door()
{
}

void Play_ManagementPart_Door::Initialize()
{
	HitBox collShape({ 3,7,1 });
	Collider coll({ -2,5,0 });
	coll.SetCollider(collShape);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);

	Test_Model_ECSver doorModel(this);
	doorModel.Load("Assets/Model/doorway.fbx");
	AddComponent<Test_Model_ECSver>(doorModel);

	transform_->position_ = XMVectorSet(0, 0, -20, 0);
}

void Play_ManagementPart_Door::Update()
{
}

void Play_ManagementPart_Door::Release()
{
}
