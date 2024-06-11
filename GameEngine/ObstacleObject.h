#pragma once
#include"Engine/GameObject/GameObject.h"
class ObstacleObject : GameObject
{
public:
	ObstacleObject(Object* parent);
	~ObstacleObject() {};

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetObstacleData(const std::string& modelName,const XMFLOAT3& colliderSize);
	void Release() override;
};

