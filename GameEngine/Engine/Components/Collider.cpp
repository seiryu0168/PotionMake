#include "Collider.h"
#include"../../DebugUI.h"
#include "Collider.h"


Collider::Collider() : Collider({0,0,0})
{
}

Collider::Collider(const XMFLOAT3& centerPos)
	:attachObject_(nullptr),
	center_(centerPos),
	isKill_(false),
	colliderType_(ColliderType::BOX_COLLIDER),
	colliderEntity_(0),
	nowHit_(false),
	prevHit_(false),
	isShowHitArea_(true)
{
#if _DEBUG
	isShowHitArea_ = true;
#else
	isShowHitArea_ = false;
#endif
}

Collider::~Collider()
{
}

void Collider::Draw()
{

}

void Collider::Release()
{
	//コライダータイプによって消す
	switch (colliderType_)
	{
	case ColliderType::BOX_COLLIDER:
		Coordinator::RemoveComponent<HitBox>(colliderEntity_);
		break;
	case ColliderType::SPHERE_COLLIDER:
		Coordinator::RemoveComponent<HitSphere>(colliderEntity_);
		break;
	case ColliderType::CAPSULE_COLLIDER:
		Coordinator::RemoveComponent<Hit_Capsule>(colliderEntity_);
		break;
	case ColliderType::OBB_COLLIDER:
		Coordinator::RemoveComponent<HitBox_OBB>(colliderEntity_);
	default:
		break;
	}
}


void Collider::SetCollisionType(const std::string& name)
{
	if (name == "struct HitBox")
		colliderType_ = ColliderType::BOX_COLLIDER;
	else if (name == "struct HitSphere")
		colliderType_ = ColliderType::SPHERE_COLLIDER;
	else if (name == "struct Hit_Capsule")
		colliderType_ = ColliderType::CAPSULE_COLLIDER;
	else if ("struct HitBox_OBB")
		colliderType_ = ColliderType::OBB_COLLIDER;
}