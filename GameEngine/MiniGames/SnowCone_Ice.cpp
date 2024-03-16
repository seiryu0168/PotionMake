#include "SnowCone_Ice.h"
#include"../Engine/Systems/ModelSystem.h"
#include"../Engine/Systems/ImageSystem.h"
#include"SnowCone_Topping.h"

SnowCone_Ice::SnowCone_Ice(Object* parent)
	:GameObject(parent,"SnowCone_Ice"),
	top_(nullptr),
	coneSize_(1.0f)
{
}

SnowCone_Ice::~SnowCone_Ice()
{
}

void SnowCone_Ice::Initialize()
{
	Image image(1,0);
	image.Load("Assets/Image/SnowCone_IceImage.png");
	image.SetPositionAtPixel({ 0,180, 0 });
	AddComponent<Image>(image);


	Test_Model_ECSver model(this);
	model.Load("Assets/Model/SnowCone_Ice.fbx");
	AddComponent<Test_Model_ECSver>(model);
	transform_->position_ = XMVectorSet(0, 2, 0, 0);
}

void SnowCone_Ice::SetColor(const XMFLOAT4& color)
{
	GetComponent<Test_Model_ECSver>().SetCustomColor(0,1,color);
}

void SnowCone_Ice::SetTopping(int topNum)
{
	if (top_)
		top_->KillMe();
	XMVECTOR pos=GetComponent<Test_Model_ECSver>().GetBone("Bone");
	top_ = Instantiate<SnowCone_Topping>(GetParent()->GetParent());
	
	Test_Model_ECSver model(top_);
	model.Load("Assets/Model/SnowCone_Topping_Adzuki.fbx");
	top_->GetTransform()->position_ = pos;
	top_->AddComponent<Test_Model_ECSver>(model);
}

void SnowCone_Ice::AddConeSize(float size)
{
	coneSize_ += size;
	GetComponent<Image>().SetSize({ 1,coneSize_,0 });
}

void SnowCone_Ice::RemoveTopping()
{
	if (top_)
		top_->KillMe();
}

void SnowCone_Ice::Release()
{
}
