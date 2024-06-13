#include "Test_Model_ECSver.h"
#include"../ResourceManager/ModelManager_ECSver.h"
#include"../GameObject/CameraManager.h"
Test_Model_ECSver::Test_Model_ECSver()
	:Test_Model_ECSver(nullptr)
{
	type_ = SHADER_TYPE::SHADER_3D;
	blendMode_ = BLEND_MODE::BLEND_DEFAULT;
	animationFrame_ = 0;
	isDraw_ = true;
	meshEntity_ = 0;
	layerNum_ = 0;
	useShadow_ = false;
	drawDistance_ = 100;
}

Test_Model_ECSver::Test_Model_ECSver(GameObject* object,int layerNum)
	:attachObject_(object),
	type_(SHADER_TYPE::SHADER_3D),
	blendMode_(BLEND_MODE::BLEND_DEFAULT),
	drawDistance_(100),
	animationFrame_(0),
	isDraw_(true),
	meshEntity_(0),
	layerNum_(layerNum),
	useShadow_(true)
{
}

bool Test_Model_ECSver::Load(const std::string& fileName)
{
	fbx_=ModelManager_ECSver::Load(fileName);
	return true;
}

void Test_Model_ECSver::RayCast(RayCastData& rayData)
{
	//ワールドの逆行列とレイの発射地点、方向ベクトルを作成
	XMMATRIX invW = XMMatrixInverse(nullptr, attachObject_->GetTransform()->GetWorldMatrix());
	XMVECTOR startVec = XMLoadFloat3(&rayData.start);
	XMVECTOR dirVec = XMVectorSet(rayData.start.x + rayData.dir.x, rayData.start.y + rayData.dir.y, rayData.start.z + rayData.dir.z, 0);

	//逆行列をかける
	XMVECTOR&& invStartVec = XMVector3TransformCoord(startVec, invW);
	dirVec = XMVector3TransformCoord(dirVec, invW);

	XMVECTOR rayVec = dirVec - invStartVec;
	XMStoreFloat3(&rayData.start, invStartVec);
	XMStoreFloat3(&rayData.dir, rayVec);
	fbx_->RayCast(rayData, *attachObject_->GetTransform());
	rayData.dist = VectorLength(rayData.hitPos - startVec);
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
	if(isDraw_&& attachObject_ != nullptr)
	fbx_->Draw(*attachObject_->GetTransform(), type_, animationFrame_);
}

void Test_Model_ECSver::Draw(int layerNum)
{
	if (layerNum != layerNum_)
		return;
	//カメラとモデルの距離がdrawDistance_より小さかったら描画
	for (int i = 0; i < CameraManager::GetCameraCount(); i++)
	{
		XMVECTOR pos = XMLoadFloat3(&CameraManager::GetCamera(i).GetPosition());
		if (VectorLength(attachObject_->GetTransform()->position_ - pos) <= drawDistance_)
		{
			Direct3D::SetBlendMode(blendMode_);
			fbx_->Draw(*attachObject_->GetTransform(), type_, animationFrame_, useShadow_);
			break;
		}
	}
}

void Test_Model_ECSver::Draw(Transform transform, SHADER_TYPE type, int frame)
{
	
	if (isDraw_)
	{
				Direct3D::SetBlendMode(blendMode_);
				fbx_->Draw(transform, type, frame, useShadow_);
		
	}
}

void Test_Model_ECSver::DrawShadow()
{
	if (isDraw_ && attachObject_ != nullptr)
	{
		bool canDraw = false;
		for (int i = 0; i < CameraManager::GetCameraCount(); i++)
		{
			XMVECTOR pos = XMLoadFloat3(&CameraManager::GetCamera(i).GetPosition());
			if (VectorLength(attachObject_->GetTransform()->position_ - pos) <= drawDistance_)
			{
				Direct3D::SetBlendMode(blendMode_);
				fbx_->DrawShadow(*attachObject_->GetTransform(), animationFrame_);
				break;
			}
		}
	}
}
