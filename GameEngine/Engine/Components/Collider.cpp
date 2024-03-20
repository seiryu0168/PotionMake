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
}