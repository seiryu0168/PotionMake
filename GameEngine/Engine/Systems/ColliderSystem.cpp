#include "ColliderSystem.h"
#include"../GameObject/GameObject.h"
#include"../DirectX_11/Direct3D.h"
#include"../GameObject/CameraManager.h"


void ColliderSystem::CreateVB()
{
	//HitBox�p�o�[�e�b�N�X�o�b�t�@
	{
		D3D11_BUFFER_DESC bd_vertex{};
		bd_vertex.ByteWidth = sizeof(VERTEX) * 8;
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex{};
		data_vertex.pSysMem = boxVertices_;
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pBoxVertexBuffer_);
		assert(hr == S_OK);
	}
	//HitSphere�p�o�[�e�b�N�X�o�b�t�@
	{
		D3D11_BUFFER_DESC bd_vertex{};
		bd_vertex.ByteWidth = sizeof(VERTEX) * 36;
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex{};
		data_vertex.pSysMem = sphereVertices_;
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pSphereVertexBuffer_);
		assert(hr == S_OK);
	}
}
void ColliderSystem::CreateIB()
{
	//HitBox�p�C���f�b�N�X�o�b�t�@
	{
	
		D3D11_BUFFER_DESC   bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * 12*3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
	
		D3D11_SUBRESOURCE_DATA InitData{};
		InitData.pSysMem = boxIndex;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pBoxIndexBuffer_);
		assert(hr == S_OK);
	}
	//
	////HitSphere�p�C���f�b�N�X�o�b�t�@
	//{
	//	D3D11_BUFFER_DESC   bd{};
	//	bd.Usage = D3D11_USAGE_DEFAULT;
	//	bd.ByteWidth = sizeof(int) * indexNum_;
	//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//	bd.CPUAccessFlags = 0;
	//	bd.MiscFlags = 0;
	//
	//	D3D11_SUBRESOURCE_DATA InitData{};
	//	InitData.pSysMem = index;
	//	InitData.SysMemPitch = 0;
	//	InitData.SysMemSlicePitch = 0;
	//	HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pBoxIndexBuffer_);
	//}
}
void ColliderSystem::CreateCB()
{
	//HitBox�p�R���X�^���g�o�b�t�@
	{

		D3D11_BUFFER_DESC cb{};
		cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		// �R���X�^���g�o�b�t�@�̍쐬
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pBoxConstantBuffer_);
		assert(hr == S_OK);
	}
	//HitSphere�p�R���X�^���g�o�b�t�@
	{

		D3D11_BUFFER_DESC cb{};
		cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		// �R���X�^���g�o�b�t�@�̍쐬
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pSphereConstantBuffer_);
		assert(hr == S_OK);
	}
}

ColliderSystem::ColliderSystem()
	: System(),
	maxDivision_(1)
{
	Coordinator::RegisterComponent<HitBox>();
	Coordinator::RegisterComponent<HitSphere>();

	cellAllay_.resize(pow(8, maxDivision_));
	int vCount_ = 0;
	XMFLOAT3 vPos = {0,0,0};
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			sphereVertices_[vCount_] = { XMVectorSet(0.5f * cosf(vPos.x), 0.5f * sinf(vPos.y), 0.5f * sinf(vPos.z), 0) };
			vPos.x += XMConvertToRadians(360.0f / 6.0f);
			vPos.z += XMConvertToRadians(360.0f / 6.0f);
			vCount_++;
		}
		vPos.x = 0;
		vPos.z = 0;
		vPos.y+= XMConvertToRadians(360.0f / 6.0f);
	}
	CreateVB();
	CreateIB();
	CreateCB();

	//Signature collSignature;
	//auto type = Coordinator::GetComponentType<HitBox>();
	//collSignature.set(Coordinator::GetComponentType<HitBox>());
	//collSignature.set(Coordinator::GetComponentType<HitSphere>());
}

void ColliderSystem::Update()
{
	//CheckCollision_Octree();
	for (auto const& firstEntity : entities_)
	{
		auto& firstCollision = Coordinator::GetComponent<Collider>(firstEntity);
		firstCollision.nowHit_ = false;
		for (auto const& secondEntity : entities_)
		{
			if (firstEntity == secondEntity)
			{
				continue;
			}
			auto& secondCollision = Coordinator::GetComponent<Collider>(secondEntity);
	
			if(firstCollision.attachObject_->IsActive()&& secondCollision.attachObject_->IsActive()&&VectorLength(firstCollision.attachObject_->GetTransform()->position_- secondCollision.attachObject_->GetTransform()->position_)<=firstCollision.collisionDistanceLimit_)
			CheckCollision(&firstCollision, &secondCollision);
		}
	}
}

void ColliderSystem::Draw(int drawLayer)
{
	ColliderType type;
	bool isShow;
	Direct3D::SetShader(SHADER_TYPE::SHADER_COLLIDER);
	//Direct3D::SetShader(SHADER_TYPE::SHADER_3D);
	Direct3D::SetBlendMode(BLEND_MODE::BLEND_DEFAULT);



	for (Entity entity : entities_)
	{
		isShow = Coordinator::GetComponent<Collider>(entity).isShowHitArea_;
		type = Coordinator::GetComponent<Collider>(entity).GetType();
		if (isShow)
		{
			//CONSTANT_BUFFER cb;
			//cb.matWVP = XMMatrixTranspose(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->GetWorldMatrix() * CameraManager::GetCurrentCamera().GetViewMatrix() * CameraManager::GetCurrentCamera().GetProjectionMatrix());
			//cb.matW = XMMatrixTranspose(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->GetWorldMatrix());
			//cb.matNormal = XMMatrixTranspose(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->GetNormalMatrix());
			
			//D3D11_MAPPED_SUBRESOURCE pdata;
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			if (type == ColliderType::BOX_COLLIDER)
			{
				CONSTANT_BUFFER cb;
				XMFLOAT3 pos = StoreFloat3(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->position_);
				XMFLOAT3 colliderPos = Coordinator::GetComponent<Collider>(entity).GetCenter();
				XMFLOAT3 colliderSize = Coordinator::GetComponent<Collider>(entity).GetCollisionShape<HitBox>().size_;
				XMMATRIX matWVP = XMMatrixScaling(colliderSize.x, colliderSize.y, colliderSize.z) *
					XMMatrixTranslation(pos.x + colliderPos.x,
						pos.y + colliderPos.y,
						pos.z + colliderPos.z) *
					CameraManager::GetCurrentCamera().GetViewMatrix() *
					CameraManager::GetCurrentCamera().GetProjectionMatrix();




				cb.matWVP = XMMatrixTranspose(matWVP);
				cb.matW = XMMatrixTranspose(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->GetWorldMatrix());
				cb.matNormal = XMMatrixTranspose(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->GetNormalMatrix());


				D3D11_MAPPED_SUBRESOURCE pdata;
				Direct3D::pContext->Map(pBoxConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); //GPU����̃f�[�^�A�N�Z�X���~�߂�
				memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));			      //�f�[�^��l�𑗂�

				Direct3D::pContext->Unmap(pBoxConstantBuffer_, 0);//�ĊJ

				//���_�o�b�t�@
				UINT stride = sizeof(VERTEX);
				UINT offset = 0;
				Direct3D::pContext->IASetVertexBuffers(0, 1, &pBoxVertexBuffer_, &stride, &offset);

				// �C���f�b�N�X�o�b�t�@�[���Z�b�g
				stride = sizeof(int);
				offset = 0;
				Direct3D::pContext->IASetIndexBuffer(pBoxIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

				//�R���X�^���g�o�b�t�@
				Direct3D::pContext->VSSetConstantBuffers(0, 1, &pBoxConstantBuffer_);				//���_�V�F�[�_�[�p	
				Direct3D::pContext->PSSetConstantBuffers(0, 1, &pBoxConstantBuffer_);				//�s�N�Z���V�F�[�_�[�p
				Direct3D::pContext->UpdateSubresource(pBoxConstantBuffer_, 0, nullptr, &cb, 0, 0);

				Direct3D::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
				Direct3D::pContext->DrawIndexed(36, 0, 0);
				Direct3D::pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			}
		}
	}
}

void ColliderSystem::Release()
{
	//�g��for�����Œl�������̂ŃR�s�[���ĉ�
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::GetComponent<Collider>(entity).Release();
		Coordinator::RemoveComponent<Collider>(entity);
		Coordinator::DestroyEntity(entity);
	}
	//for (int i = 0; i < cellAllay_.size(); i++)
	//{
	//	cellAllay_[i].clear();
	//}
}

void ColliderSystem::CheckRemove()
{
	//�g��for�����Œl�������̂ŃR�s�[���ĉ�
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		const auto& collider = Coordinator::GetComponent<Collider>(entity);
		if (Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->IsDead())
		{
			
			//for (auto itr = cellAllay_[collider.currentAccessNumber_].begin(); itr != cellAllay_[collider.currentAccessNumber_].end();)
			//{
			//	if (*itr == collider.currentAccessNumber_)
			//	{
			//		itr = cellAllay_[collider.currentAccessNumber_].erase(itr);
			//	}
			//	else
			//		itr++;
			//}
			Coordinator::GetComponent<Collider>(entity).Release();
			Coordinator::RemoveComponent<Collider>(entity);
		}
	}
}

void ColliderSystem::CheckCollision(Collider* firstTarget, Collider* secondTarget) const
{
	bool isCollision = false;
	//�R���C�_�[�̃^�C�v�ŏ����ς���
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
		case ColliderType::CAPSULE_COLLIDER:
			isCollision = false;//IsHitCapsule_Box(secondTarget, firstTarget);
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

	case ColliderType::CAPSULE_COLLIDER:
		switch (secondTarget->GetType())
		{
		case ColliderType::BOX_COLLIDER:
			isCollision = false;//IsHitCapsule_Box(firstTarget, secondTarget);
			break;
		}
	case ColliderType::OBB_COLLIDER:
		switch (secondTarget->GetType())
		{
		case ColliderType::BOX_COLLIDER:
			isCollision = false;
			break;
		case ColliderType::SPHERE_COLLIDER:
			isCollision = false;
			break;
		case ColliderType::OBB_COLLIDER:
			isCollision = IsHitOBB_OBB(firstTarget, secondTarget);
			break;
		}
	default:
		break;
	}

	if (isCollision)
	{
			firstTarget->nowHit_ = true;
			firstTarget->GetAttachedObject()->OnCollisionStay(secondTarget->GetAttachedObject());
	}
}

void ColliderSystem::CheckCollision_Octree()
{
	//������Ԃ̎Z�o�A�o�^���s��
	for (auto const firstEntity : entities_)
	{
		auto& collider = Coordinator::GetComponent<Collider>(firstEntity);
		collider.CalcAccessNumber();
		UINT  accessNum = collider.GetCurrentAccessNumber();
		int  prevAccessNum = collider.GetPrevAccessNumber();
		//�O�t���[���̋�Ԕԍ��ƍ��̋�Ԕԍ����������
		if (accessNum != prevAccessNum)
		{
			if (prevAccessNum == -1)
			{
				cellAllay_[accessNum].push_back(firstEntity);
				//collider.SetItr(std::prev(cellAllay_[accessNum].end()));
			}
			else
			{
				//auto itr = collider.GetItr();
				//itr = cellAllay_[prevAccessNum].erase(itr);

				for (auto itr = cellAllay_[prevAccessNum].begin();itr!=cellAllay_[prevAccessNum].end();)
				{
					if (*itr == collider.GetPrevAccessNumber())
					{
						itr = cellAllay_[prevAccessNum].erase(itr);
					}
					else
						itr++;
				}
				cellAllay_[accessNum].push_back(firstEntity);
			}
			collider.SetPrevAccessNumber(accessNum);
		}
	}

	//��Ԃ������ďՓ˔�����`�F�b�N����
	//�ċA�֐��g���\��
	CreateCollisionList(0);

}

void ColliderSystem::CreateCollisionList(UINT accessNum)
{
	//������Ԓ��̓����蔻��`�F�b�N
	for (auto firstEntity : cellAllay_[accessNum])
	{
		auto& firstCollision = Coordinator::GetComponent<Collider>(firstEntity);
		firstCollision.nowHit_ = false;
		for (auto const& secondEntity : cellAllay_[accessNum])
		{
			if (firstEntity == secondEntity)
			{
				continue;
			}
			auto& secondCollision = Coordinator::GetComponent<Collider>(secondEntity);

			if (firstCollision.attachObject_->IsActive() &&
				secondCollision.attachObject_->IsActive())
			CheckCollision(&firstCollision, &secondCollision);
		}
	}
	//�ՓˑΉ����X�g�Ə�����ԂƂ̏Փ˔���
	for (auto firstEntity : collisionList_)
	{
		auto& firstCollision = Coordinator::GetComponent<Collider>(firstEntity);
		firstCollision.nowHit_ = false;
		for (auto const& secondEntity : cellAllay_[accessNum])
		{
			if (firstEntity == secondEntity)
			{
				continue;
			}
			auto& secondCollision = Coordinator::GetComponent<Collider>(secondEntity);

			if (firstCollision.attachObject_->IsActive() &&
			    secondCollision.attachObject_->IsActive())
			CheckCollision(&firstCollision, &secondCollision);
		}
	}

	//�q��Ԃ̃A�N�Z�X�ԍ����v�Z
	UINT childCellNum = (accessNum << 3) + 1;
	size_t size = cellAllay_.size();
	//�q��Ԃ������Ă���ꍇ
	if (size > childCellNum)
	{
		//�ՓˑΉ����X�g�ɍ��̋�ԓ��̃R���W������ǉ�
		for (auto firstEntity : cellAllay_[accessNum])
		{
			collisionList_.push_back(firstEntity);
		}
		//���̋�Ԃ̓����蔻��
		for (int i = 0; i < 8; i++)
		{
			if (size > childCellNum + i)
				CreateCollisionList(childCellNum + i);
		}
		//�ՓˑΉ����X�g���獡�̋�Ԃɂ���R���W�������O��
		for (int i = 0; i < cellAllay_[accessNum].size(); i++)
		{
			collisionList_.pop_back();
		}
	}
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
		//firstTarget->HitEnable(true);
		return true;
	}

	//firstTarget->HitEnable(false);
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
		//firstTarget->HitEnable(true);
		return true;
	}

	//firstTarget->HitEnable(false);
	return false;
}

//bool ColliderSystem::IsHitCapsule_Box(Collider* firstTarget, Collider* secondTarget) const
//{
//	Hit_Capsule capsule = firstTarget->GetCollisionShape<Hit_Capsule>();
//	HitBox box = secondTarget->GetCollisionShape<HitBox>();
//	XMFLOAT3 boxPos = StoreFloat3(firstTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&firstTarget->GetCenter()));
//
//
//	XMVECTOR dirVec = XMVector3Normalize(XMVectorSet(0,1,0,0) * firstTarget->GetAttachedObject()->GetTransform()->GetWorldRotateMatrix());
//
//	XMVECTOR pVec = secondTarget->GetAttachedObject()->GetTransform()->position_ - (firstTarget->GetAttachedObject()->GetTransform()->position_ + dirVec* capsule.length_);
//	
//	float distance = 0;
//	if (VectorDot(XMVector3Normalize(pVec), dirVec) > 0)
//	{
//		if ((boxPos.x + box.size_.x) > (spherePos.x - radius) &&
//			(boxPos.x - box.x) < (spherePos.x + radius) &&
//			(boxPos.y + box.y) > (spherePos.y - radius) &&
//			(boxPos.y - box.y) < (spherePos.y + radius) &&
//			(boxPos.z + box.z) > (spherePos.z - radius) &&
//			(boxPos.z - box.z) < (spherePos.z + radius))
//		{
//			return true;
//		}
//		//distance = VectorLength(pVec - (firstTarget->GetAttachedObject()->GetTransform()->position_ + dirVec * capsule.length_));
//		if (distance <= capsule.radius_)
//			return true;
//	}
//	pVec = secondTarget->GetAttachedObject()->GetTransform()->position_ - (firstTarget->GetAttachedObject()->GetTransform()->position_ - dirVec * capsule.length_);
//
//	if (VectorDot(XMVector3Normalize(pVec), dirVec) < 0)
//	{
//		distance = VectorLength(pVec - (firstTarget->GetAttachedObject()->GetTransform()->position_ - dirVec * capsule.length_));
//		if (distance <= capsule.radius_)
//			return true;
//	}
//	
//
//	XMVECTOR aVec = firstTarget->GetAttachedObject()->GetTransform()->position_ - dirVec * capsule.length_;
//
//	XMVECTOR nearPoint = aVec + (dirVec * VectorDot(dirVec, pVec));
//	
//
//	distance = VectorLength(secondTarget->GetAttachedObject()->GetTransform()->position_ - nearPoint);
//
//	if (distance <= capsule.radius_)
//	{
//		return true;
//	}
//		
//	return false;
//}

bool ColliderSystem::IsHitCapsule_Capsule(Collider* firstTarget, Collider* secondTarget) const
{
	Hit_Capsule firstCapsule = firstTarget->GetCollisionShape<Hit_Capsule>();
	Hit_Capsule secondCapsule = firstTarget->GetCollisionShape<Hit_Capsule>();
	
	//firstTarget�̃x�N�g��
	XMVECTOR first_Start = secondTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&firstTarget->GetCenter());
	XMVECTOR firstDirVec = XMVectorSet(0, 1, 0, 0) * firstTarget->GetAttachedObject()->GetTransform()->GetWorldRotateMatrix();
	first_Start -= firstDirVec * firstCapsule.length_*0.5f;

	//secondTarget�̃x�N�g��
	XMVECTOR second_Start = secondTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&secondTarget->GetCenter());
	XMVECTOR secondDirVec = XMVectorSet(0, 1, 0, 0) * secondTarget->GetAttachedObject()->GetTransform()->GetWorldRotateMatrix();
	second_Start -= secondDirVec * secondCapsule.length_ * 0.5f;

	XMVECTOR VecSecondToFirst = first_Start - second_Start;

	float t1 = ((VectorDot(firstDirVec, secondDirVec) * VectorDot(secondDirVec, VecSecondToFirst) - (VectorDot(secondDirVec, secondDirVec) * VectorDot(firstDirVec, VecSecondToFirst))))
			 / ((VectorDot(firstDirVec, firstDirVec) * VectorDot(secondDirVec, secondDirVec)) - (VectorDot(firstDirVec, secondDirVec) * VectorDot(firstDirVec, secondDirVec)));

	XMVECTOR P_First = first_Start + (t1 * firstDirVec);
	float t2 = VectorDot(secondDirVec, (P_First - second_Start)) / VectorDot(secondDirVec, secondDirVec);
	XMVECTOR P_Second = first_Start + (t2 * secondDirVec);

	


	return false;
}

bool ColliderSystem::IsHitOBB_OBB(Collider* firstTarget, Collider* secondTarget) const
{
	XMVECTOR obbPos_first = firstTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&firstTarget->GetCenter());
	XMVECTOR obbPos_second = secondTarget->GetAttachedObject()->GetTransform()->position_ + XMLoadFloat3(&secondTarget->GetCenter());

	HitBox_OBB& hitObb_first = firstTarget->GetCollisionShape<HitBox_OBB>();
	HitBox_OBB& hitObb_second = secondTarget->GetCollisionShape<HitBox_OBB>();

	XMVECTOR betweenCenterPoint = obbPos_first - obbPos_second;

	hitObb_first.CalcAxisVec(XMQuaternionRotationMatrix(firstTarget->GetAttachedObject()->GetTransform()->GetWorldRotateMatrix()));
	hitObb_second.CalcAxisVec(XMQuaternionRotationMatrix(secondTarget->GetAttachedObject()->GetTransform()->GetWorldRotateMatrix()));

	XMVECTOR dir_firstX_  = XMVector3Normalize(hitObb_first.vecX_);
	XMVECTOR dir_firstY_  = XMVector3Normalize(hitObb_first.vecY_);
	XMVECTOR dir_firstZ_  = XMVector3Normalize(hitObb_first.vecZ_);
	XMVECTOR dir_secondX_ = XMVector3Normalize(hitObb_second.vecX_);
	XMVECTOR dir_secondY_ = XMVector3Normalize(hitObb_second.vecY_);
	XMVECTOR dir_secondZ_ = XMVector3Normalize(hitObb_second.vecZ_);


	//firstTarget�̒��S�_����̒���
	float rA = VectorLength(hitObb_first.vecX_);	
	float rB = hitObb_first.prjLine(&hitObb_first.vecX_, &hitObb_second.vecX_, &hitObb_second.vecY_, &hitObb_second.vecZ_);		//obbB�̒��S�_����̒���
	float  L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(hitObb_first.vecX_))));//���S�_�Ԃ̒���
	if (L > rA + rB)
	{
		return false;
	}

	rA = XMVectorGetX(XMVector3Length(hitObb_first.vecY_));								    //obbA�̒��S�_����̒���
	rB = hitObb_first.prjLine(&hitObb_first.vecY_, &hitObb_second.vecX_, &hitObb_second.vecY_, &hitObb_second.vecZ_);			//obbB�̒��S�_����̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(hitObb_first.vecY_))));//���S�_�Ԃ̒���
	if (L > rA + rB)
	{
		return false;
	}

	rA = XMVectorGetX(XMVector3Length(hitObb_first.vecZ_));								    //obbA�̒��S�_����̒���
	rB = hitObb_first.prjLine(&hitObb_first.vecZ_, &hitObb_second.vecX_, &hitObb_second.vecY_, &hitObb_second.vecZ_);			//obbB�̒��S�_����̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(hitObb_first.vecZ_))));//���S�_�Ԃ̒���
	if (L > rA + rB)
	{
		return false;
	}

	rA = XMVectorGetX(XMVector3Length(hitObb_second.vecX_));								    //obbA�̒��S�_����̒���
	rB = hitObb_second.prjLine(&hitObb_second.vecX_, &hitObb_first.vecX_, &hitObb_first.vecY_, &hitObb_first.vecZ_);			//obbB�̒��S�_����̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(hitObb_second.vecX_))));//���S�_�Ԃ̒���
	if (L > rA + rB)
	{
		return false;
	}

	rA = XMVectorGetX(XMVector3Length(hitObb_second.vecY_));								    //obbA�̒��S�_����̒���
	rB = hitObb_second.prjLine(&hitObb_second.vecY_, &hitObb_first.vecX_, &hitObb_first.vecY_, &hitObb_first.vecZ_);			//obbB�̒��S�_����̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(hitObb_second.vecY_))));//���S�_�Ԃ̒���
	if (L > rA + rB)
	{
		return false;
	}

	rA = XMVectorGetX(XMVector3Length(hitObb_second.vecZ_));								    //obbA�̒��S�_����̒���
	rB = hitObb_second.prjLine(&hitObb_second.vecZ_, &hitObb_first.vecX_, &hitObb_first.vecY_, &hitObb_first.vecZ_);			//obbB�̒��S�_����̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(hitObb_second.vecZ_))));//���S�_�Ԃ̒���
	if (L > rA + rB)
	{
		return false;
	}

	///////////////////////////////��������O�ώ��ɂ��Փ˔���//////////////////////////////////////

	XMVECTOR cross;
	//firstTarget��X����secondTarget��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstX_, dir_secondX_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecY_, &hitObb_first.vecZ_);				//obbA�̒���
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecY_, &hitObb_second.vecZ_);				//obbB�̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//firstTarget��X����secondTarget��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstX_, dir_secondY_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecY_, &hitObb_first.vecZ_);				//obbA�̒���
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecX_, &hitObb_second.vecZ_);				//obbB�̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//firstTarget��X����secondTarget��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstX_, dir_secondZ_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecY_, &hitObb_first.vecZ_);				//obbA�̒���
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecX_, &hitObb_second.vecY_);				//obbB�̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//firstTarget��Y����secondTarget��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstY_, dir_secondX_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecX_, &hitObb_first.vecZ_);				//obbA�̒���
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecY_, &hitObb_second.vecZ_);				//obbB�̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//firstTarget��Y����secondTarget��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstY_, dir_secondY_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecX_, &hitObb_first.vecZ_);				//obbA�̒���
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecX_, &hitObb_second.vecZ_);				//obbB�̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//firstTarget��Y����secondTarget��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstY_, dir_secondZ_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecX_, &hitObb_first.vecZ_);				//obbA�̒���
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecX_, &hitObb_second.vecY_);				//obbB�̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//firstTarget��Z����secondTarget��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstZ_,dir_secondX_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecX_, &hitObb_first.vecY_);				//obbA�̒���
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecX_, &hitObb_second.vecZ_);				//obbB�̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//firstTarget��Z����secondTarget��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstZ_, dir_secondY_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecX_, &hitObb_first.vecY_);				//obbA�̒���
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecX_, &hitObb_second.vecZ_);				//obbB�̒���
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//firstTarget��Z����secondTarget��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	cross = XMVector3Normalize(XMVector3Cross(dir_firstZ_, dir_secondZ_));
	rA = hitObb_first.prjLine(&cross, &hitObb_first.vecX_, &hitObb_first.vecY_);
	rB = hitObb_second.prjLine(&cross, &hitObb_second.vecX_, &hitObb_second.vecY_);
	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
	if (L > rA + rB)
	{
		return false;
	}

	//���S�_�Ԃ̋���������rA + rB�ȏ�ɂȂ�Ȃ������̂œ������Ă���
	return true;
}

//bool Collider::IsHitOBB_Sphere(OBBCollider* obb, SphereCollider* sphere)
//{
//	XMFLOAT3 obbPos = obb->pColObject_->GetTransform().position_;
//	XMFLOAT3 spherePos = sphere->pColObject_->GetTransform().position_;
//
//	XMVECTOR betweenCenterPoint = XMLoadFloat3(&spherePos) - XMLoadFloat3(&obbPos);
//
//	obb->CalcAxisVec();
//
//	float L;
//	double rA = XMVectorGetX(XMVector3Length(obb->OBB_X));								    //obb�̒��S�_����̒���
//	double rB = sphere->size_.x;															//sphere�̒��S�_����̒���
//	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(obb->OBB_X))));//���S�_�Ԃ̒���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	rA = XMVectorGetX(XMVector3Length(obb->OBB_Y));								    //obbA�̒��S�_����̒���
//	rB = sphere->size_.x;															//obbB�̒��S�_����̒���
//	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(obb->OBB_Y))));//���S�_�Ԃ̒���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	rA = XMVectorGetX(XMVector3Length(obb->OBB_Z));								    //obbA�̒��S�_����̒���
//	rB = sphere->size_.x;															//obbB�̒��S�_����̒���
//	L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(obb->OBB_Z))));//���S�_�Ԃ̒���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//#if false
//	rA = XMVectorGetX(XMVector3Length(obbB->OBB_X));								    //obbA�̒��S�_����̒���
//	rB = sphere->size_.x;														//obbB�̒��S�_����̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(obbB->OBB_X))));//���S�_�Ԃ̒���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	rA = XMVectorGetX(XMVector3Length(obbB->OBB_Y));								    //obbA�̒��S�_����̒���
//	rB = obbA->prjLine(&obbB->OBB_Y, &obbA->OBB_X, &obbA->OBB_Y, &obbA->OBB_Z);			//obbB�̒��S�_����̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(obbB->OBB_Y))));//���S�_�Ԃ̒���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	rA = XMVectorGetX(XMVector3Length(obbB->OBB_Z));								    //obbA�̒��S�_����̒���
//	rB = obbA->prjLine(&obbB->OBB_Z, &obbA->OBB_X, &obbA->OBB_Y, &obbA->OBB_Z);			//obbB�̒��S�_����̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(obbB->OBB_Z))));//���S�_�Ԃ̒���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	///////////////////////////////��������O�ώ��ɂ��Փ˔���//////////////////////////////////////
//
//	XMVECTOR cross;
//	//obbA��X����obbB��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nX, obbB->nX));
//	rA = obbA->prjLine(&cross, &obbA->OBB_Y, &obbA->OBB_Z);				//obbA�̒���
//	rB = obbA->prjLine(&cross, &obbB->OBB_Y, &obbB->OBB_Z);				//obbB�̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//obbA��X����obbB��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nX, obbB->nY));
//	rA = obbA->prjLine(&cross, &obbA->OBB_Y, &obbA->OBB_Z);				//obbA�̒���
//	rB = obbA->prjLine(&cross, &obbB->OBB_X, &obbB->OBB_Z);				//obbB�̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//obbA��X����obbB��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nX, obbB->nZ));
//	rA = obbA->prjLine(&cross, &obbA->OBB_Y, &obbA->OBB_Z);				//obbA�̒���
//	rB = obbA->prjLine(&cross, &obbB->OBB_X, &obbB->OBB_Y);				//obbB�̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//obbA��Y����obbB��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nY, obbB->nX));
//	rA = obbA->prjLine(&cross, &obbA->OBB_X, &obbA->OBB_Z);				//obbA�̒���
//	rB = obbA->prjLine(&cross, &obbB->OBB_Y, &obbB->OBB_Z);				//obbB�̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//obbA��Y����obbB��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nY, obbB->nY));
//	rA = obbA->prjLine(&cross, &obbA->OBB_X, &obbA->OBB_Z);				//obbA�̒���
//	rB = obbA->prjLine(&cross, &obbB->OBB_X, &obbB->OBB_Z);				//obbB�̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//obbA��Y����obbB��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nY, obbB->nZ));
//	rA = obbA->prjLine(&cross, &obbA->OBB_X, &obbA->OBB_Z);				//obbA�̒���
//	rB = obbA->prjLine(&cross, &obbB->OBB_X, &obbB->OBB_Y);				//obbB�̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//obbA��Z����obbB��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nZ, obbB->nX));
//	rA = obbA->prjLine(&cross, &obbA->OBB_X, &obbA->OBB_Y);				//obbA�̒���
//	rB = obbA->prjLine(&cross, &obbB->OBB_Y, &obbB->OBB_Z);				//obbB�̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//obbA��Z����obbB��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nZ, obbB->nY));
//	rA = obbA->prjLine(&cross, &obbA->OBB_X, &obbA->OBB_Y);				//obbA�̒���
//	rB = obbA->prjLine(&cross, &obbB->OBB_X, &obbB->OBB_Z);				//obbB�̒���
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//obbA��Z����obbB��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
//	cross = XMVector3Normalize(XMVector3Cross(obbA->nZ, obbB->nZ));
//	rA = obbA->prjLine(&cross, &obbA->OBB_X, &obbA->OBB_Y);
//	rB = obbA->prjLine(&cross, &obbB->OBB_X, &obbB->OBB_Y);
//	L = fabs(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
//	if (L > rA + rB)
//	{
//		return false;
//	}
//
//	//���S�_�Ԃ̋���������rA + rB�ȏ�ɂȂ�Ȃ������̂œ������Ă���
//#endif
//	return true;
//}
