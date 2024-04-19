#include "P_CP_Player_ItemGetter.h"
#include"Engine/Systems/ColliderSystem.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"P_CP_ResourceItem.h"
P_CP_Player_ItemGetter::P_CP_Player_ItemGetter(Object* parent)
	:GameObject(parent,"P_CP_Player_ItemGetter")
{
}

P_CP_Player_ItemGetter::~P_CP_Player_ItemGetter()
{
}

void P_CP_Player_ItemGetter::Initialize()
{
	HitSphere sphere(1);
	Collider coll({ 0,0,0 });
	coll.SetAttachObject(this);
	coll.SetCollider(sphere);
	AddComponent<Collider>(coll);

	Test_Model_ECSver model(this);
	model.Load("Assets/Model/flower_red3.fbx");
	AddComponent<Test_Model_ECSver>(model);
}

void P_CP_Player_ItemGetter::Start()
{
}

void P_CP_Player_ItemGetter::Update()
{

	targetItemNum_ = -1;

}

void P_CP_Player_ItemGetter::Release()
{
}

void P_CP_Player_ItemGetter::OnCollisionStay(GameObject* pTarget)
{
	if (pTarget->GetTag() == "ResourceItem")
	{
		if (targetItemNum_ < 0)
		{
			targetItemNum_ = ((P_CP_ResourceItem*)pTarget)->GetItemNumber();
			hitItem_ = pTarget;
		}
	}
}
