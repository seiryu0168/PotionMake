#include "Play_ManagementPart_Door.h"
#include"../../Engine/Systems/ModelSystem.h"
#include"../../Engine/Systems/ColliderSystem.h"

Play_ManagementPart_Door::Play_ManagementPart_Door(Object* parent)
	:ManagementPartObjectBase(parent,"Play_ManagementPart_Door")
{
}

Play_ManagementPart_Door::~Play_ManagementPart_Door()
{
}

void Play_ManagementPart_Door::Initialize()
{
	accessUINum_ = 0;
	actionName_ = "äOèo";
	HitBox collShape({ 1,7,3 });
	Collider coll({ 0,5,3 });
	coll.SetCollider(collShape);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);

	Test_Model_ECSver doorModel(this);
	doorModel.Load("Assets/Model/doorway.fbx");
	AddComponent<Test_Model_ECSver>(doorModel);

	transform_->position_ = XMVectorSet(20.5f, 0, 0, 0);
	transform_->RotateEular(0, 90, 0);
	transform_->scale_ = { 1.3f,1.3f,1.3f };
}

void Play_ManagementPart_Door::Update()
{
}

void Play_ManagementPart_Door::Release()
{
}
