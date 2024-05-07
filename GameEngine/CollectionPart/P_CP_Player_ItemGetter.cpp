#include "P_CP_Player_ItemGetter.h"
#include "P_CP_ResourceItem.h"
#include "../Engine/Systems/ColliderSystem.h"
#include "../Engine/Systems/ModelSystem.h"
#include "../Engine/DirectX_11/Input.h"
P_CP_Player_ItemGetter::P_CP_Player_ItemGetter(Object* parent)
	:GameObject(parent,"P_CP_Player_ItemGetter"),
	targetItemNum_(-1)
{
}

P_CP_Player_ItemGetter::~P_CP_Player_ItemGetter()
{
}

void P_CP_Player_ItemGetter::Initialize()
{
	//当たり判定の設定
	HitSphere sphere(1);
	Collider coll({ 0,0,0 });
	coll.SetAttachObject(this);
	coll.SetCollider(sphere);
	AddComponent<Collider>(coll);

	
	Test_Model_ECSver model(this);
	model.Load("Assets/Model/flower_red3.fbx");
	AddComponent<Test_Model_ECSver>(model);
	transform_->position_ = XMVectorSet(0, 100, 0, 0);
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
	//当たったオブジェクトが素材なら
	if (pTarget->GetTag() == "ResourceItem")
	{
		if (targetItemNum_ < 0)
		{
			targetItemNum_ = ((P_CP_ResourceItem*)pTarget)->GetItemNumber();
			hitItem_ = pTarget;
		}
	}
}
