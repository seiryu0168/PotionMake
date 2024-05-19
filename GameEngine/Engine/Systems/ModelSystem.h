#pragma once
#include"../ECS/System.h"
#include"../Components/Test_Model_ECSver.h"
class ModelSystem : public System
{
public:
	ModelSystem();
	~ModelSystem() {};
	//void Update() override;
	void Draw(int layerNum) override;
	void DrawShadow();
	void Release() override;
	void CheckRemove() override;
};

