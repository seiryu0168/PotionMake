#include "CollectionPart_Ground.h"
#include "../Engine/Systems/ModelSystem.h"
CollectionPart_Ground::CollectionPart_Ground(Object* parent)
	:GameObject(parent,"CollectionPart_Ground")
{
}

CollectionPart_Ground::~CollectionPart_Ground()
{
}

void CollectionPart_Ground::Initialize()
{
	//’n–Ê‚Ìƒ‚ƒfƒ‹
	Test_Model_ECSver groundModel(this);
	groundModel.Load("Assets/Model/Ground02.fbx");
	AddComponent<Test_Model_ECSver>(groundModel);
	transform_->scale_ = { 2,2,2 };
}

void CollectionPart_Ground::Start()
{
}

void CollectionPart_Ground::Update()
{
}

void CollectionPart_Ground::Release()
{
}
