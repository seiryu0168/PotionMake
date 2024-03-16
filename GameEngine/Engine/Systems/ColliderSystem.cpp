#include "ColliderSystem.h"
#include"../GameObject/GameObject.h"
ColliderSystem::ColliderSystem() : System()
{
	Coordinator::RegisterComponent<HitBox>();
	Coordinator::RegisterComponent<HitSphere>();
	//Signature collSignature;
	//auto type = Coordinator::GetComponentType<HitBox>();
	//collSignature.set(Coordinator::GetComponentType<HitBox>());
	//collSignature.set(Coordinator::GetComponentType<HitSphere>());
}

void ColliderSystem::Update()
{
	
	for (auto const& firstEntity : entities_)
	{
		auto& firstCollision = Coordinator::GetComponent<Collider>(firstEntity);
		for (auto const& secondEntity : entities_)
		{
			if (firstEntity == secondEntity)
			{
				continue;
			}
			auto& secondCollision = Coordinator::GetComponent<Collider>(secondEntity);

			CheckCollision(&firstCollision, &secondCollision);
		}
	}
}

void ColliderSystem::Release()
{
	//拡張for文内で値を消すのでコピーして回す
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::GetComponent<Collider>(entity).Release();
		Coordinator::RemoveComponent<Collider>(entity);
		Coordinator::DestroyEntity(entity);
	}
}

void ColliderSystem::CheckRemove()
{
	//拡張for文内で値を消すのでコピーして回す
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		if (Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->IsDead())
		{
			Coordinator::GetComponent<Collider>(entity).Release();
			Coordinator::RemoveComponent<Collider>(entity);
		}
	}
}

void ColliderSystem::CheckCollision(Collider* firstTarget, Collider* secondTarget) const
{
	bool isCollision = false;
	//コライダーのタイプで処理変える
	switch (firstTarget->GetType())
	{
	case ColliderType::BOX_COLLIDER:
		switch (secondTarget->GetType())
		{
		case ColliderType::BOX_COLLIDER:
			isCollision = IsHitBox_Box(firstTarget, secondTarget);
			break;
		case ColliderType::SPHERE_COLLIDER:
			isCollision = IsHitBox_Sphere(firstTarget, secondTarget);
			break;
		default:
			break;
		}
		break;
	case ColliderType::SPHERE_COLLIDER:
		switch (secondTarget->GetType())
		{
		case ColliderType::BOX_COLLIDER:
			isCollision = IsHitBox_Sphere(secondTarget, firstTarget);
			break;
		case ColliderType::SPHERE_COLLIDER:
			isCollision = IsHitSphere_Sphere(firstTarget, secondTarget);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	//当たってたらオブジェクトの関数を呼び出す
	if (isCollision)
		firstTarget->GetAttachedObject()->OnCollision(secondTarget->GetAttachedObject());

}

bool ColliderSystem::IsHitBox_Box(Collider* firstTarget,Collider* secondTarget) const
{
	XMFLOAT3 boxPos1 = StoreFloat3(firstTarget->GetAttachedObject()->GetComponent<Transform>().position_ + XMLoadFloat3(&firstTarget->GetCenter()));
	XMFLOAT3 boxPos2 = StoreFloat3(secondTarget->GetAttachedObject()->GetComponent<Transform>().position_ + XMLoadFloat3(&secondTarget->GetCenter()));

	if ((boxPos1.x + firstTarget->GetCollisionShape<HitBox>().size_.x) > (boxPos2.x - secondTarget->GetCollisionShape<HitBox>().size_.x) &&
		(boxPos1.x - firstTarget->GetCollisionShape<HitBox>().size_.x) < (boxPos2.x + secondTarget->GetCollisionShape<HitBox>().size_.x) &&
		(boxPos1.y + firstTarget->GetCollisionShape<HitBox>().size_.y) > (boxPos2.y - secondTarget->GetCollisionShape<HitBox>().size_.y) &&
		(boxPos1.y - firstTarget->GetCollisionShape<HitBox>().size_.y) < (boxPos2.y + secondTarget->GetCollisionShape<HitBox>().size_.y) &&
		(boxPos1.z + firstTarget->GetCollisionShape<HitBox>().size_.z) > (boxPos2.z - secondTarget->GetCollisionShape<HitBox>().size_.z) &&
		(boxPos1.z - firstTarget->GetCollisionShape<HitBox>().size_.z) < (boxPos2.z + secondTarget->GetCollisionShape<HitBox>().size_.z))
	{
		firstTarget->HitEnable(true);
		return true;
	}

	firstTarget->HitEnable(false);
	return false;
}

bool ColliderSystem::IsHitBox_Sphere(Collider* boxTarget, Collider* sphereTarget) const
{
	XMFLOAT3 boxPos = StoreFloat3(boxTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&boxTarget->GetCenter()));
	XMFLOAT3 spherePos = StoreFloat3(sphereTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&sphereTarget->GetCenter()));
	XMFLOAT3 box = boxTarget->GetCollisionShape<HitBox>().size_;
	float radius = sphereTarget->GetCollisionShape<HitSphere>().radius_;
	
	if ((boxPos.x + box.x) > (spherePos.x - radius) &&
		(boxPos.x - box.x) < (spherePos.x + radius) &&
		(boxPos.y + box.y) > (spherePos.y - radius) &&
		(boxPos.y - box.y) < (spherePos.y + radius) &&
		(boxPos.z + box.z) > (spherePos.z - radius) &&
		(boxPos.z - box.z) < (spherePos.z + radius))
	{
		return true;
	}
	return false;
}

bool ColliderSystem::IsHitSphere_Sphere(Collider* firstTarget, Collider* secondTarget) const
{
	XMVECTOR spherePos1 = firstTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&firstTarget->GetCenter());
	XMVECTOR spherePos2 = secondTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&secondTarget->GetCenter());
	float sphereDistance = VectorLength(spherePos2 - spherePos1);
	float distance = firstTarget->GetCollisionShape<HitSphere>().radius_ + secondTarget->GetCollisionShape<HitSphere>().radius_;

	if (sphereDistance < distance)
	{
		firstTarget->HitEnable(true);
		return true;
	}

	firstTarget->HitEnable(false);
	return false;
}
