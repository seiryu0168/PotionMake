#include "ColliderSystem.h"
#include"../GameObject/GameObject.h"
#include"../DirectX_11/Direct3D.h"
#include"../GameObject/CameraManager.h"
void ColliderSystem::CreateVB()
{
	//HitBox用バーテックスバッファ
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
	}
	//HitSphere用バーテックスバッファ
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
	}
}
void ColliderSystem::CreateIB()
{
	////HitBox用インデックスバッファ
	//{
	//
	//	D3D11_BUFFER_DESC   bd{};
	//	bd.Usage = D3D11_USAGE_DEFAULT;
	//	bd.ByteWidth = sizeof(int) * 8;
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
	//
	////HitSphere用インデックスバッファ
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
	//HitBox用コンスタントバッファ
	{

		D3D11_BUFFER_DESC cb{};
		cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		// コンスタントバッファの作成
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pBoxConstantBuffer_);
	}
	//HitSphere用コンスタントバッファ
	{

		D3D11_BUFFER_DESC cb{};
		cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		// コンスタントバッファの作成
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pSphereConstantBuffer_);
	}
}
ColliderSystem::ColliderSystem() : System()
{
	Coordinator::RegisterComponent<HitBox>();
	Coordinator::RegisterComponent<HitSphere>();

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
		vPos.y+= XMConvertToRadians(360.0f / 6.0f);
	}
	CreateVB();
	CreateCB();

	//Signature collSignature;
	//auto type = Coordinator::GetComponentType<HitBox>();
	//collSignature.set(Coordinator::GetComponentType<HitBox>());
	//collSignature.set(Coordinator::GetComponentType<HitSphere>());
}

void ColliderSystem::Update()
{
	
	for (auto const& firstEntity : entities_)
	{
		auto& firstCollision = Coordinator::GetComponent<Collider>(firstEntity);
		for (auto const& secondEntity : entities_)
		{
			if (firstEntity == secondEntity)
			{
				continue;
			}
			auto& secondCollision = Coordinator::GetComponent<Collider>(secondEntity);

			CheckCollision(&firstCollision, &secondCollision);
		}
	}
}

void ColliderSystem::Draw(int drawLayer)
{
	ColliderType type;
	bool isShow;
	Direct3D::SetShader(SHADER_TYPE::SHADER_COLLIDER);
	Direct3D::SetBlendMode(BLEND_MODE::BLEND_DEFAULT);
	for (Entity entity : entities_)
	{
		isShow = Coordinator::GetComponent<Collider>(entity).isShowHitArea_;
		type = Coordinator::GetComponent<Collider>(entity).GetType();
		if (isShow)
		{
			CONSTANT_BUFFER cb;
			cb.matWVP = XMMatrixTranspose(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->GetWorldMatrix() * CameraManager::GetCurrentCamera().GetViewMatrix() * CameraManager::GetCurrentCamera().GetProjectionMatrix());
			cb.matW = XMMatrixTranspose(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->GetWorldMatrix());
			cb.matNormal = XMMatrixTranspose(Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->GetTransform()->GetNormalMatrix());
			
			D3D11_MAPPED_SUBRESOURCE pdata;
			if (type == ColliderType::BOX_COLLIDER)
			{
				Direct3D::pContext->Map(pBoxConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); //GPUからのデータアクセスを止める
				memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));			      //データを値を送る
				Direct3D::pContext->Unmap(pBoxConstantBuffer_, 0);//再開
			}
			else if (type == ColliderType::SPHERE_COLLIDER)
			{
				Direct3D::pContext->Map(pSphereConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); //GPUからのデータアクセスを止める
				memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));			      //データを値を送る
				Direct3D::pContext->Unmap(pSphereConstantBuffer_, 0);//再開
			}

			//頂点バッファ
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			if (type == ColliderType::BOX_COLLIDER)
			{
				Direct3D::pContext->IASetVertexBuffers(0, 1, &pBoxVertexBuffer_, &stride, &offset);
				//コンスタントバッファ
				Direct3D::pContext->VSSetConstantBuffers(0, 1, &pBoxConstantBuffer_);							//頂点シェーダー用	
				Direct3D::pContext->PSSetConstantBuffers(0, 1, &pBoxConstantBuffer_);							//ピクセルシェーダー用
				Direct3D::pContext->UpdateSubresource(pBoxConstantBuffer_, 0, nullptr, &cb, 0, 0);
				Direct3D::pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				Direct3D::pContext->Draw(sizeof(boxVertices_)/sizeof(VERTEX),0);
			}
			else if (type == ColliderType::SPHERE_COLLIDER)
			{

				Direct3D::pContext->IASetVertexBuffers(0, 1, &pSphereVertexBuffer_, &stride, &offset);

				//コンスタントバッファ
				Direct3D::pContext->VSSetConstantBuffers(0, 1, &pSphereConstantBuffer_);							//頂点シェーダー用	
				Direct3D::pContext->PSSetConstantBuffers(0, 1, &pSphereConstantBuffer_);							//ピクセルシェーダー用
				Direct3D::pContext->UpdateSubresource(pSphereConstantBuffer_, 0, nullptr, &cb, 0, 0);
				Direct3D::pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				Direct3D::pContext->Draw(sizeof(sphereVertices_) / sizeof(VERTEX), 0);
			}
		}
	}
}

void ColliderSystem::Release()
{
	//拡張for文内で値を消すのでコピーして回す
	std::set<Entity> subEntity = entities_;
	for (Entity entity : subEntity)
	{
		Coordinator::GetComponent<Collider>(entity).Release();
		Coordinator::RemoveComponent<Collider>(entity);
		Coordinator::DestroyEntity(entity);
	}
}

void ColliderSystem::CheckRemove()
{
	//拡張for文内で値を消すのでコピーして回す
	std::set<Entity> subEntities = entities_;
	for (Entity entity : subEntities)
	{
		if (Coordinator::GetComponent<Collider>(entity).GetAttachedObject()->IsDead())
		{
			Coordinator::GetComponent<Collider>(entity).Release();
			Coordinator::RemoveComponent<Collider>(entity);
		}
	}
}

void ColliderSystem::CheckCollision(Collider* firstTarget, Collider* secondTarget) const
{
	bool isCollision = false;
	//コライダーのタイプで処理変える
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
	default:
		break;
	}
	//当たってたらオブジェクトの関数を呼び出す
	if (isCollision)
		firstTarget->GetAttachedObject()->OnCollision(secondTarget->GetAttachedObject());

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
		firstTarget->HitEnable(true);
		return true;
	}

	firstTarget->HitEnable(false);
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
		firstTarget->HitEnable(true);
		return true;
	}

	firstTarget->HitEnable(false);
	return false;
}
