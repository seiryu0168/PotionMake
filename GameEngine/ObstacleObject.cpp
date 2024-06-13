#include "ObstacleObject.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/Systems/ColliderSystem.h"

ObstacleObject::ObstacleObject(Object* parent)
	:GameObject(parent,"ObstacleObject")
{
}

void ObstacleObject::Initialize()
{
}

void ObstacleObject::Start()
{
}

void ObstacleObject::Update()
{
}

void ObstacleObject::SetObstacleData(const std::string& modelName, const XMFLOAT3& colliderSize)
{
	//ƒ‚ƒfƒ‹‚Ìƒ[ƒh‚Æ•`‰æ‹——£İ’è
	Test_Model_ECSver model(this);
	model.Load(modelName);
	model.SetDrawDistance(300);
	AddComponent<Test_Model_ECSver>(model);

	//“–‚½‚è”»’èİ’è
	HitBox box(colliderSize);
	Collider coll({ 0,0,0 });
	coll.SetAttachObject(this);
	coll.SetCollider(box);
	AddComponent<Collider>(coll);
}

void ObstacleObject::Release()
{
}
