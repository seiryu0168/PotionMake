#include "BoxCollider.h"

BoxCollider::BoxCollider()
	: BoxCollider({0,0,0}, {1,1,1})
{
}

BoxCollider::BoxCollider(const XMFLOAT3& basePos, const XMFLOAT3& size)
	: Collider(basePos), size_(size)
{
}

BoxCollider::~BoxCollider()
{
}

//�Փ˔���
//���������I�u�W�F�N�g�̓����蔻�肪target�ɓ���
//bool BoxCollider::IsHit(Collider* target)
//{
//	switch (target->type_)
//	{
//	case BOX_COLLIDER:
//		return IsHitBox_Box((BoxCollider*)target, this);
//
//	case SPHERE_COLLIDER:
//		return IsHitBox_Sphere(this, (SphereCollider*)target);
//	}
//}