#include "Test_Model_ECSver.h"
#include"../ResourceManager/ModelManager_ECSver.h"
Test_Model_ECSver::Test_Model_ECSver()
	:Test_Model_ECSver(nullptr)
{
}

Test_Model_ECSver::Test_Model_ECSver(GameObject* object,int layerNum)
	:attachObject_(object),
	type_(SHADER_TYPE::SHADER_3D),
	animationFrame_(0),
	isDraw_(true),
	meshEntity_(0),
	layerNum_(layerNum)
{
}

bool Test_Model_ECSver::Load(const std::string& fileName)
{
	fbx_=ModelManager_ECSver::Load(fileName);
	return true;
}

void Test_Model_ECSver::RayCast(RayCastData& rayData)
{
	fbx_->RayCast(rayData, *attachObject_->GetTransform());
}

const XMVECTOR Test_Model_ECSver::GetBone(const std::string& boneName)
{
	XMVECTOR pos= XMLoadFloat3(&fbx_->GetBonePosition(boneName));
	return pos * attachObject_->GetTransform()->GetWorldMatrix();
}

const XMVECTOR Test_Model_ECSver::GetBone(const UINT& partsNum, const UINT& num)
{
	XMVECTOR pos = XMLoadFloat3(&fbx_->GetBonePosition(partsNum, num));
	return pos * attachObject_->GetTransform()->GetWorldMatrix();
}

const std::string Test_Model_ECSver::GetBoneName(const UINT& partsNum, const UINT& num)
{
	return fbx_->GetBonename(partsNum,num);
}

const UINT Test_Model_ECSver::GetBoneCount()
{
	return fbx_->GetBoneCount();
}

void Test_Model_ECSver::SetCustomColor(int partsNum, int materialNum, const XMFLOAT4& color)
{
	fbx_->SetColor(partsNum, materialNum, color);
}

void Test_Model_ECSver::Draw()
{
	if(isDraw_)
	fbx_->Draw(*attachObject_->GetTransform(), type_, animationFrame_);
}

void Test_Model_ECSver::Draw(int layerNum)
{
	if (layerNum != layerNum_)
		return;

	if (isDraw_)
		fbx_->Draw(*attachObject_->GetTransform(), type_, animationFrame_);
}
