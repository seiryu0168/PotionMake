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
	//モデルのロードと描画距離設定
	Test_Model_ECSver model(this);
	model.Load(modelName);
	model.SetDrawDistance(300);
	AddComponent<Test_Model_ECSver>(model);

	//当たり判定設定
	HitBox box(colliderSize);
	Collider coll({ 0,0,0 });
	coll.SetAttachObject(this);
	coll.SetCollider(box);
	AddComponent<Collider>(coll);
}

void ObstacleObject::Release()
{
}
