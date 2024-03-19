#include "ManagementPart_Floor.h"
#include"Engine/Systems/ModelSystem.h"
ManagementPart_Floor::ManagementPart_Floor(Object* parent)
	:GameObject(parent,"ManagementPart_Floor"),
	rotate_(0)
{
}

ManagementPart_Floor::~ManagementPart_Floor()
{
}

void ManagementPart_Floor::Initialize()
{
	Test_Model_ECSver floorModel(this);
	floorModel.Load("Assets/Model/ground_grass.fbx");
	AddComponent<Test_Model_ECSver>(floorModel);
	transform_->scale_ = { 10,10,10 };
}

void ManagementPart_Floor::Update()
{
	//rotate_ += 1;
	//transform_->RotateEular(0, rotate_, 0);
}

void ManagementPart_Floor::Release()
{
}
