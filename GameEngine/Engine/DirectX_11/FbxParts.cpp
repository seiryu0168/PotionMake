#include "FbxParts.h"
#include"Math.h"
//#include"../ResourceManager/Model.h"
#include"../GameObject/CameraManager.h"
#include"Direct3D.h"
#include <filesystem>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<memory>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <crtdbg.h>
#else
#define DEBUG_NEW	
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#endif // _DEBUG
FbxParts::FbxParts()
{
	boneNum_ = 0;
	materialCount_ = 0;
	polygonCount_ = 0;
	vertexCount_ = 0;

	indexCount_ = nullptr;
	pBoneArray_ = nullptr;
	//pMaterialList_ = nullptr;
	pSkinInfo_ = nullptr;
	pVertices_ = nullptr;
	pWeightArray_ = nullptr;
	ppCluster_ = nullptr;
	ppIndex_ = nullptr;

	pVertexBuffer_ = nullptr;
	ppIndexBuffer_ = nullptr;
	pConstantBuffer_ = nullptr;
	pToonTexture_ = nullptr;

}

FbxParts::~FbxParts()
{
	//SAFE_RELEASE_DELETE(pToonTexture_);

	//SAFE_DELETE(pVertices_);
	//SAFE_DELETE(indexCount_);

	for (int i = 0; i < materialCount_; i++)
	{
		//SAFE_DELETE_ARRAY(ppIndex_[i]);
		SAFE_RELEASE(ppIndexBuffer_[i]);
		//SAFE_RELEASE_DELETE(pMaterialList_[i].pTexture);
		//SAFE_RELEASE_DELETE(pMaterialList_[i].pNormalMap);
	}
	//SAFE_DELETE_ARRAY(ppIndex_);
	//SAFE_DELETE_ARRAY(pMaterialList_);
	SAFE_RELEASE(pVertexBuffer_);
	//SAFE_DELETE_ARRAY(ppIndexBuffer_);
	SAFE_RELEASE(pConstantBuffer_);

	//SAFE_DELETE_ARRAY(ppCluster_);
	if (pWeightArray_ != nullptr)
	{
		for (int i = 0; i < vertexCount_; i++)
		{
			//SAFE_DELETE_ARRAY(pWeightArray_[i].pBoneIndex);
			//SAFE_DELETE_ARRAY(pWeightArray_[i].pBoneWeight);
			//SAFE_DELETE_ARRAY(pBoneArray_);
		}
			//SAFE_DELETE_ARRAY(pWeightArray_);
	}
	if(pSkinInfo_)
	pSkinInfo_->Destroy();
	
}

HRESULT FbxParts::Init(FbxNode* pNode)
{
	FbxMesh* mesh = pNode->GetMesh();
	pToonTexture_ = std::make_unique<Texture>();
	pToonTexture_->Load("../Image\\ToonTexture.jpg");
	
	//各情報の個数を取得
	vertexCount_ = mesh->GetControlPointsCount();	//頂点の数
	polygonCount_ = mesh->GetPolygonCount();	//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount();//マテリアルの数

	InitIndex(mesh);
	InitVertex(mesh);
	CreateConstantBuffer();
	InitMaterial(pNode);
	InitSkelton(mesh);
	//mesh->Destroy();
	//pSkinInfo_;
	return S_OK;
}

void FbxParts::Draw(Transform& transform,XMFLOAT4 lineColor, bool useShadow)
{
	transform.Calclation();
	static float factor[4] = { D3D11_BLEND_ZERO,D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };

	
	//コンスタントバッファに情報を渡す
	for (int i = 0; i < materialCount_; i++)
	{
		CONSTANT_BUFFER cb;
		cb.matWVP  = XMMatrixTranspose(transform.GetWorldMatrix() *
			   CameraManager::GetCurrentCamera().GetViewMatrix() *
			   CameraManager::GetCurrentCamera().GetProjectionMatrix());

		cb.matW		 = XMMatrixTranspose(transform.GetWorldMatrix());
		cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());

		cb.matWLP = XMMatrixTranspose(transform.GetWorldMatrix() *
								      Direct3D::GetLightViewMatrix() *
									  Direct3D::GetLightProjectionMatrix());

		cb.matWLPT = XMMatrixTranspose(transform.GetWorldMatrix() *
									   Direct3D::GetLightViewMatrix() *
									   Direct3D::GetLightProjectionMatrix() *
									   Direct3D::GetClipToUVMatrix());

		cb.lightDirection = Direct3D::GetLightDirection();
		XMFLOAT3 cameraPos = CameraManager::GetCurrentCamera().GetPosition();
		cb.cameraPosition = XMFLOAT4(cameraPos.x, cameraPos.y, cameraPos.z, 0);

		cb.isTexture = materialList_[i].GetTexture() != nullptr;
		cb.isNormal = materialList_[i].GetNormalMap() != nullptr;
		cb.diffuseColor = materialList_[i].GetDiffuse();
		cb.ambient = materialList_[i].GetAmbient();
		cb.speculer = materialList_[i].GetSpeculer();
		cb.shininess = materialList_[i].GetShininess();
		cb.customColor = materialList_[i].GetCustomColor();

		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); //GPUからのデータアクセスを止める
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));			      //データを値を送る
		if (cb.isTexture)
		{
			ID3D11SamplerState* pSampler = ((Texture*)materialList_[i].GetTexture().get())->GetSampler();
			Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);
			ID3D11ShaderResourceView* pSRV1 = ((Texture*)materialList_[i].GetTexture().get())->GetSRV();

			Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV1);
		}
		if (cb.isNormal)
		{
			ID3D11ShaderResourceView* pNormalSRV = ((Texture*)materialList_[i].GetNormalMap().get())->GetSRV();
			Direct3D::pContext->PSSetShaderResources(2, 1, &pNormalSRV);
		}
		if (useShadow)
		{
			//Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); //GPUからのデータアクセスを止める
			//memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));			      //データを値を送る

			//ID3D11SamplerState* pToonSampler = pToonTexture_->GetSampler();
			//Direct3D::pContext->PSSetSamplers(1, 1, &pToonSampler);
			//ID3D11ShaderResourceView* pToonSRV = pToonTexture_->GetSRV();
			//Direct3D::pContext->PSSetShaderResources(1, 1, &pToonSRV);

			ID3D11SamplerState* depthSampler = Direct3D::GetDepthSampler();
			ID3D11ShaderResourceView* pDepthSRV = Direct3D::GetDepthSRV();
			Direct3D::pContext->PSSetSamplers(2, 1, &depthSampler);
			Direct3D::pContext->PSSetShaderResources(3, 1, &pDepthSRV);
			//Direct3D::pContext->Unmap(pConstantBuffer_, 0);//再開
		}
		Direct3D::pContext->Unmap(pConstantBuffer_, 0);//再開


		//頂点バッファ
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
		
		// インデックスバッファーをセット
		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext->IASetIndexBuffer(ppIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

		//コンスタントバッファ
		Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);				//頂点シェーダー用	
		Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);				//ピクセルシェーダー用
		Direct3D::pContext->UpdateSubresource(pConstantBuffer_, 0, nullptr, &cb, 0, 0);
		Direct3D::pContext->DrawIndexed(indexCount_.get()[i], 0, 0);
	}
}

void FbxParts::DrawSkinAnime(Transform& transform, FbxTime time, XMFLOAT4 lineColor)
{
	for (int i = 0; i < boneNum_; i++)
	{
		//各ボーンの現在の行列を取得
		FbxAnimEvaluator* evaluator = ppCluster_[i]->GetLink()->GetScene()->GetAnimationEvaluator();
		FbxMatrix mCurrentOrentation = evaluator->GetNodeGlobalTransform(ppCluster_[i]->GetLink(), time);

		//行列コピー
		XMFLOAT4X4 pose;
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++) 
			{
				pose(x, y) = (float)mCurrentOrentation.Get(x, y);
			}
		}

		//オフセット時とのポーズの差分を計算
		pBoneArray_[i].newPose = XMLoadFloat4x4(&pose);
		pBoneArray_[i].diffPose = XMMatrixInverse(nullptr, pBoneArray_[i].bindPose);
		pBoneArray_[i].diffPose *= pBoneArray_[i].newPose;
	}
	//各ボーンに対応する頂点の変形を制御
	for (int i = 0; i < vertexCount_; i++)
	{
		//各頂点ごとに影響するボーン×ウェイトを反映させた行列を作成
		XMMATRIX matrix;
		ZeroMemory(&matrix, sizeof(matrix));
		for (int j = 0; j < boneNum_; j++)
		{
			if (pWeightArray_[i].pBoneIndex[j] < 0)
				break;
			matrix += pBoneArray_[pWeightArray_[i].pBoneIndex[j]].diffPose * pWeightArray_[i].pBoneWeight[j];
		}
		//作成した行列で頂点を変形
		XMVECTOR pos = pWeightArray_[i].originPos;
		XMVECTOR normal = pWeightArray_[i].originNormal;
		pVertices_[i].position = XMVector3TransformCoord(pos, matrix);
		pVertices_[i].normal = XMVector3TransformCoord(normal, matrix);
	}

	//頂点バッファをロックし、変形後の頂点情報で上書き
	D3D11_MAPPED_SUBRESOURCE msr = {};
	Direct3D::pContext->Map(pVertexBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	if (msr.pData)
	{
		memcpy_s(msr.pData, msr.RowPitch, pVertices_.get(), sizeof(VERTEX) * vertexCount_);
		Direct3D::pContext->Unmap(pVertexBuffer_, 0);
	}
	Draw(transform,lineColor);
}

void FbxParts::DrawShadow(Transform& transform)
{
	transform.Calclation();
	static float factor[4] = { D3D11_BLEND_ZERO,D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };


	//コンスタントバッファに情報を渡す
	for (int i = 0; i < materialCount_; i++)
	{
		CONSTANT_BUFFER cb;
		cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * CameraManager::GetCurrentCamera().GetViewMatrix() * CameraManager::GetCurrentCamera().GetProjectionMatrix());
		cb.matW = XMMatrixTranspose(transform.GetWorldMatrix());
		cb.matWLP= XMMatrixTranspose(transform.GetWorldMatrix() *
								 	 Direct3D::GetLightViewMatrix() *
								     Direct3D::GetLightProjectionMatrix());
		cb.matWLPT = XMMatrixTranspose(transform.GetWorldMatrix() *
									   Direct3D::GetLightViewMatrix() *
									   Direct3D::GetLightProjectionMatrix() *
									   Direct3D::GetClipToUVMatrix());
		cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());
		//matWVPの光源バージョン
		//XMMATRIX matWLP = XMMatrixTranspose(transform.GetWorldMatrix() *
		//									Direct3D::GetLightViewMatrix() *
		//	        CameraManager::GetCurrentCamera().GetProjectionMatrix());

		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); //GPUからのデータアクセスを止める
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));			      //データを値を送る
		
		//ID3D11ShaderResourceView* depthView = Direct3D::GetDepthSRV();
		//ID3D11SamplerState* depthSampler = Direct3D::GetDepthSampler();
		//Direct3D::pContext->PSSetSamplers(2, 1, &depthSampler);
		//Direct3D::pContext->PSSetShaderResources(3, 1, &depthView);
		//if (cb.isTexture)
		//{
		//	ID3D11SamplerState* pSampler = ((Texture*)materialList_[i].GetTexture().get())->GetSampler();
		//	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);
		//	ID3D11ShaderResourceView* pSRV1 = ((Texture*)materialList_[i].GetTexture().get())->GetSRV();
		//
		//	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV1);
		//}
		//if (cb.isNormal)
		//{
		//	ID3D11ShaderResourceView* pNormalSRV = ((Texture*)materialList_[i].GetNormalMap().get())->GetSRV();
		//	Direct3D::pContext->PSSetShaderResources(2, 1, &pNormalSRV);
		//}
		Direct3D::pContext->Unmap(pConstantBuffer_, 0);//再開

		//Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); //GPUからのデータアクセスを止める
		//memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&matWLP), sizeof(matWLP));			      //データを値を送る

		//ID3D11SamplerState* pToonSampler = pToonTexture_->GetSampler();
		//Direct3D::pContext->PSSetSamplers(1, 1, &pToonSampler);
		//ID3D11ShaderResourceView* pToonSRV = pToonTexture_->GetSRV();
		//Direct3D::pContext->PSSetShaderResources(1, 1, &pToonSRV);
		//Direct3D::pContext->Unmap(pConstantBuffer_, 0);//再開

		//頂点バッファ
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

		// インデックスバッファーをセット
		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext->IASetIndexBuffer(ppIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

		//コンスタントバッファ
		Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);				//頂点シェーダー用	
		Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);				//ピクセルシェーダー用
		Direct3D::pContext->UpdateSubresource(pConstantBuffer_, 0, nullptr, &cb, 0, 0);
		Direct3D::pContext->DrawIndexed(indexCount_.get()[i], 0, 0);
	}
}

HRESULT FbxParts::InitVertex(fbxsdk::FbxMesh* mesh)
{
	//頂点情報を入れる配列
	pVertices_ = std::make_unique<VERTEX[]>(vertexCount_);

	//全ポリゴン
	for (DWORD poly = 0; poly < (DWORD)polygonCount_; poly++)
	{
		FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = mesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = mesh->GetControlPointAt(index);
			pVertices_[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//頂点のUV
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			pVertices_[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);

			//頂点の法線
			FbxVector4 Normal;
			mesh->GetPolygonVertexNormal(poly, vertex, Normal);	//ｉ番目のポリゴンの、ｊ番目の頂点の法線をゲット
			pVertices_[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		}
			int index0 = mesh->GetPolygonVertex(poly, 0);
			int index1 = mesh->GetPolygonVertex(poly, 1);
			int index2 = mesh->GetPolygonVertex(poly, 2);

		if (mesh->GetElementTangentCount() > 0)
		{
			int cnt = mesh->GetElementTangentCount();
			for (int vertex = 0; vertex < 3; vertex++)
			{
				int index = mesh->GetPolygonVertex(poly, vertex);
				//接線
				FbxGeometryElementTangent* t = mesh->GetElementTangent(0);
				FbxVector4 tangent = t->GetDirectArray().GetAt(index).mData;
				pVertices_[index].tangent = XMVectorSet((float)tangent[0], (float)tangent[1], (float)tangent[2], 0.0f);

			}
		}
		else
		{
			CalcTangent(pVertices_[index0], pVertices_[index1], pVertices_[index2]);
			CalcTangent(pVertices_[index1], pVertices_[index2], pVertices_[index0]);
			CalcTangent(pVertices_[index2], pVertices_[index0], pVertices_[index1]);
		}


#if 0
			if (mesh->GetElementTangentCount() > 0)
			{
				int cnt = mesh->GetElementTangentCount();
				for (int vertex = 0; vertex < 3; vertex++)
				{
					int index = mesh->GetPolygonVertex(poly, vertex);
					//接線
					FbxGeometryElementTangent* t = mesh->GetElementTangent(0);
					FbxVector4 tangent = t->GetDirectArray().GetAt(index).mData;
					pVertices_[index].tangent = XMVectorSet((float)tangent[0], (float)tangent[1], (float)tangent[2], 0.0f);

				}
			}
		else
		{
			//for (int vertex = 0; vertex < 3; vertex++)
			//{
			//	int index = mesh->GetPolygonVertex(poly, vertex);
			//	pVertices_[index].tangent = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			//}
		}
#endif
	}
	FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
	int UVNum = pUV->GetDirectArray().GetCount();
	int UVCount = mesh->GetTextureUVCount();
	int indexNum = pUV->GetIndexArray().GetCount();

	//一つの頂点に複数のUV座標が割り当てられている可能性があるのでそこら辺どうにかしないといけない
	if (vertexCount_ <= UVCount)
	{
		UVCount = vertexCount_;
	}
	if (pUV->GetMappingMode() == FbxLayerElement::eByControlPoint)
	{
		for (int i = 0; i < UVCount; i++)
		{
			FbxVector2  uv = pUV->GetDirectArray().GetAt(i);
			pVertices_[i].uv = XMVectorSet((float)uv.mData[0], 1.0f-(float)(uv.mData[1]), 0.0f, 0.0f);;
		}
	}
	//if (pUV->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
	//{
	//	if (((FbxLayerElement*)pUV)->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
	//	{
	//		for (int i = 0; i < UVCount; i++)
	//		{
	//			int ind= pUV->GetIndexArray().GetAt(i);
	//			FbxVector2  uv = pUV->GetDirectArray().GetAt(ind);
	//			XMVECTOR UV = XMVectorZero();
	//			UV= XMVectorSet((float)uv.mData[0], 1.0f-(float)(uv.mData[1]), 0.0f, 0.0f);
	//			UV.m128_i8[0] = 0;
	//			UV.m128_u8[0] = 0;
	//			pVertices_[i].uv = UV;
	//			if (sizeof(UV.m128_i8) > sizeof(pVertices_[i].uv.m128_i8))
	//			{
	//				int a = 0;
	//			}
	//		}
	//	}
	//}

	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = pVertices_.get();
	HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/FbxParts.cpp:頂点データ用バッファの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

/////////////////////////////インデックス///////////////////////////////////
HRESULT FbxParts::InitIndex(fbxsdk::FbxMesh* mesh)
{
	ppIndex_ = std::make_unique<std::unique_ptr<int[]>[]>(materialCount_);
	ppIndexBuffer_ = std::make_unique<ID3D11Buffer*[]>(materialCount_);
	indexCount_ = std::make_unique<int[]>(materialCount_);

	for (int i = 0; i < materialCount_; i++)
	{
		int count = 0;
		ppIndex_[i] = std::make_unique<int[]>(polygonCount_ * 3);
		//全ポリゴン
		for (DWORD poly = 0; poly < (DWORD)polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			if (mtlId == i)
			{
				//3頂点分
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					ppIndex_[i][count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
		}
		indexCount_.get()[i] = count;

		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = ppIndex_[i].get();
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &ppIndexBuffer_[i]);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"DirectX_11/FbxParts.cpp:インデックスバッファの作成に失敗", L"エラー", MB_OK);
			return hr;
		}
	}
	return S_OK;
}

//////////////////////////////////コンスタントバッファ作成///////////////////////////////////	
HRESULT FbxParts::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	HRESULT hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/FbxParts.cpp:コンスタントバッファの作成に失敗", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

HRESULT FbxParts::InitSkelton(FbxMesh* pMesh)
{
	pSkinInfo_ = (FbxSkin*)pMesh->GetDeformer(0);
	if (pSkinInfo_ == nullptr)
	{
		return S_OK;
	}
	//pSkinInfo_ = (FbxSkin*)pDeformer;

	struct POLY_INDEX
	{
		int* polyIndex;
		int* vertexIndex;
		int refNum;
	};

	/*POLY_INDEX* polyTable = new POLY_INDEX[vertexCount_];
	for (int i = 0; i < vertexCount_; i++)
	{
		polyTable[i].polyIndex = new int[polygonCount_ * 3];
		polyTable[i].vertexIndex = new int[polygonCount_ * 3];
		polyTable[i].refNum = 0;
		ZeroMemory(polyTable[i].polyIndex, sizeof(int)* polygonCount_ * 3);
		ZeroMemory(polyTable[i].vertexIndex, sizeof(int)* polygonCount_ * 3);

		for (int j = 0; j < polygonCount_; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (pMesh->GetPolygonVertex(j, k) == i)
				{
					polyTable[i].polyIndex[polyTable[i].refNum] = j;
					polyTable[i].vertexIndex[polyTable[i].refNum] = k;
					polyTable[i].refNum++;
				}
			}
		}
	}*/

	//ボーン情報取得
	boneNum_ = pSkinInfo_->GetClusterCount();
	ppCluster_ = std::make_unique<FbxCluster*[]>(boneNum_);
	for (int i = 0; i < boneNum_; i++)
	{
		ppCluster_[i] = pSkinInfo_->GetCluster(i);
	}

	//ボーンの数に合わせてウェイト情報を準備
	pWeightArray_ = std::make_unique<FbxParts::WEIGHT[]>(vertexCount_);
	for (int i = 0; i < vertexCount_; i++)
	{
		pWeightArray_[i].originPos = pVertices_[i].position;
		pWeightArray_[i].originNormal = pVertices_[i].normal;
		pWeightArray_[i].pBoneIndex = std::make_unique<int[]>(boneNum_);
		pWeightArray_[i].pBoneWeight = std::make_unique<float[]>(boneNum_);
		for (int j = 0; j < boneNum_; j++)
		{
			pWeightArray_[i].pBoneIndex[j] = -1;
			pWeightArray_[i].pBoneWeight[j] = 0.0f;
		}
	}

	//各ボーンから影響を受ける頂点を調べ、頂点ベースでboneIndex、Weightを整頓する
	for (int i = 0; i < boneNum_; i++)
	{
		int indexNum = ppCluster_[i]->GetControlPointIndicesCount();
		int* piIndex = ppCluster_[i]->GetControlPointIndices();
		double* pdWeight = ppCluster_[i]->GetControlPointWeights();
		
		//頂点に関連付けられたウェイト情報が5つ以上の場合は重みの大きい順で4本に絞る
		for (int j = 0; j < indexNum; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (k >= boneNum_)
					break;
				if (pdWeight[j] > pWeightArray_[piIndex[j]].pBoneWeight[k])
				{
					for (int l = boneNum_ - 1; l > k; l--)
					{
						pWeightArray_[piIndex[j]].pBoneIndex[l] = pWeightArray_[piIndex[j]].pBoneIndex[l - 1];
						pWeightArray_[piIndex[j]].pBoneWeight[l] = pWeightArray_[piIndex[j]].pBoneWeight[l - 1];
					}
					pWeightArray_[piIndex[j]].pBoneIndex[k] = i;
					pWeightArray_[piIndex[j]].pBoneWeight[k] = (float)pdWeight[j];
				}
			}
		}
	}
	
	//ボーンの生成
	pBoneArray_ = std::make_unique<FbxParts::BONE[]>(boneNum_);
	for (int i = 0; i < boneNum_; i++)
	{
		//ボーンのデフォルト位置を取得
		FbxAMatrix matrix;
		ppCluster_[i]->GetTransformLinkMatrix(matrix);

		//行列をコピー
		XMFLOAT4X4 pose;
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				pose(x, y) = (float)matrix.Get(x, y);
			}
		}
		pBoneArray_[i].bindPose = XMLoadFloat4x4(&pose);
	}

	//pSkinInfo_->Destroy();
	////一時的に取っておいたメモリ開放
	//for (int i = 0; i < vertexCount_; i++)
	//{
	//	SAFE_DELETE_ARRAY(polyTable[i].polyIndex);
	//	SAFE_DELETE_ARRAY(polyTable[i].vertexIndex);
	//}
	//SAFE_DELETE_ARRAY(polyTable);
	return E_NOTIMPL;
}

void FbxParts::InitMaterial(fbxsdk::FbxNode* pNode)
{
	materialList_ = std::make_unique<Material[]>(materialCount_);

	for (int i = 0; i < materialCount_; i++)
	{
		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		//フォンシェーディングの為にマテリアル情報を取り出す
		FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//受け取り用の各マテリアルパラメータの初期化
		FbxDouble3 diffuse = FbxDouble3(0, 0, 0);
		FbxDouble3 ambient = FbxDouble3(0, 0, 0);
		FbxDouble3 speculer = FbxDouble3(0, 0, 0);

		diffuse = pPhong->Diffuse;
		ambient = pPhong->Ambient;
		//diffuseとambientを入れる
		materialList_[i].SetDiffuse(XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f));
		materialList_[i].SetAmbient(XMFLOAT4((float)ambient[0], (float)ambient[1], (float)ambient[2], 1.0f));
		
		//PhongのクラスなのかLambertのクラスなのかを判別(Lambertだとスペキュラーの値を扱えない)
		if (pPhong->GetClassId().Is(FbxSurfacePhong::ClassId))
		{
			speculer = pPhong->Specular;
			materialList_[i].SetSpeculer(XMFLOAT4((float)speculer[0], (float)speculer[1], (float)speculer[2], 1.0f));
			//blenderだと1-粗さの値x100にあたる
			materialList_[i].SetShininess((float)pPhong->Shininess);
		}

		//テクスチャの枚数
		//pMaterialList_[i].pTexture = lProperty.GetSrcObjectCount<FbxFileTexture>();
		int count = lProperty.GetSrcObjectCount<FbxFileTexture>();
		if (lProperty.GetSrcObjectCount<FbxFileTexture>() > 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			std::filesystem::path textureFilePath = textureInfo->GetRelativeFileName();

			//パス名をファイル名と拡張子だけにする
			//char name[_MAX_FNAME];	//ファイル名
			//char ext[_MAX_EXT];		//拡張子
			//_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			//sprintf_s(name, "%s%s", name, ext);

			//wchar_t wtext[FILENAME_MAX];
			//size_t ret;
			//mbstowcs_s(&ret, wtext, name, strlen(name));

			std::wstring fName = L"../Image\\" + textureFilePath.filename().wstring();
			//ファイルからテクスチャ作成
			std::unique_ptr<Texture> pTex= std::make_unique<Texture>();
			pTex->Load(fName.c_str());
			materialList_[i].SetTexture(std::move(pTex));
		}

		//テクスチャ無し
		else
		{
			//マテリアルの色
			FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)pNode->GetMaterial(i);
			FbxDouble3  diffuse = pMaterial->Diffuse;
			materialList_[i].SetDiffuse(XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f));
		}

		/////////////////////////////////ノーマルマップ//////////////////////////
		std::unique_ptr<Texture> pNormal = std::make_unique<Texture>();
		{
			FbxProperty IPropaty = pMaterial->FindProperty(FbxSurfaceMaterial::sBump);
			int normalMapCount = IPropaty.GetSrcObjectCount<FbxFileTexture>();

			if (normalMapCount != 0)
			{
				FbxFileTexture* textureInfo = IPropaty.GetSrcObject<FbxFileTexture>(0);
				std::filesystem::path textureFilePath = textureInfo->GetRelativeFileName();

				//ファイル名+拡張だけにする
				//char name[_MAX_FNAME];	//ファイル名
				//char ext[_MAX_EXT];	//拡張子
				//_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);

				//sprintf_s(name, "%s%s", name, ext);

				//ファイルからテクスチャ作成
				//wchar_t wtext[FILENAME_MAX];
				//size_t ret;
				//mbstowcs_s(&ret, wtext, name, strlen(name));

				pNormal->Load(textureFilePath.filename().c_str());
				materialList_[i].SetNormalMap(std::move(pNormal));
			}
			else
			{
				pNormal->Load(L"../Image\\DefaultNormalMap.jpg");
				materialList_[i].SetNormalMap(std::move(pNormal));
			}
		}
	}
}

void FbxParts::CalcTangent(VERTEX& vertex0, const VERTEX& vertex1, const VERTEX& vertex2)
{
	//3頂点の必要な情報
	XMFLOAT3 localPos[3] = { StoreFloat3(vertex0.position),
							 StoreFloat3(vertex1.position),
							 StoreFloat3(vertex2.position) };

	XMFLOAT3 uv[3] =	   { StoreFloat3(vertex0.uv),	
							 StoreFloat3(vertex1.uv),
							 StoreFloat3(vertex2.uv) };
	XMVECTOR vPos0[3] = {
		XMVectorSet(localPos[0].x,uv[0].x,uv[0].y,0.0f),
		XMVectorSet(localPos[0].y,uv[0].x,uv[0].y,0.0f),
		XMVectorSet(localPos[0].z,uv[0].x,uv[0].y,0.0f)
	};
	XMVECTOR vPos1[3] = {
		XMVectorSet(localPos[1].x,uv[1].x,uv[1].y,0.0f),
		XMVectorSet(localPos[1].y,uv[1].x,uv[1].y,0.0f),
		XMVectorSet(localPos[1].z,uv[1].x,uv[1].y,0.0f)
	};
	XMVECTOR vPos2[3] = {
		XMVectorSet(localPos[2].x,uv[2].x,uv[2].y,0.0f),
		XMVectorSet(localPos[2].y,uv[2].x,uv[2].y,0.0f),
		XMVectorSet(localPos[2].z,uv[2].x,uv[2].y,0.0f)
	};

	float u[3];
	float v[3];
	for (int i = 0; i < 3; i++)
	{
		XMVECTOR V1 = vPos1[i] - vPos0[i];
		XMVECTOR V2 = vPos2[i] - vPos1[i];
		XMFLOAT3 normal;

		normal=StoreFloat3(XMVector3Normalize(XMVector3Cross(V1, V2)));
		bool degnerate = max(normal.x, 0.0f);

		if (normal.x==0.0f)
		{
			normal.x = 1.0f;
			//頂点座標かUV座標が完全に重なっているので縮退している
			//計算が成り立たない
			//assert(false);
			//XMVECTOR tangent = vertex1.position - vertex0.position;
			//tangent = tangent - vertex0.normal * VectorDot(tangent, vertex0.normal);
			//vertex0.tangent = XMVector3Normalize(tangent);
			//return;
		}

		u[i] = -normal.y / normal.x;
		v[i] = -normal.z / normal.x;
	}
	XMVECTOR tan = XMVectorSet(u[0], u[1], u[2], 0);
	//tan -= vertex0.normal * VectorDot(tan, vertex0.normal);
	vertex0.tangent = XMVector3Normalize(tan);
}

bool FbxParts::GetBonePosition(std::string boneName, XMFLOAT3* position)
{
	for (int i = 0; i < boneNum_; i++)
	{
		if (boneName == ppCluster_[i]->GetLink()->GetName())
		{
			FbxAMatrix matrix;
			ppCluster_[i]->GetTransformLinkMatrix(matrix);
			position->x = (float)matrix[3][0];
			position->y = (float)matrix[3][1];
			position->z = (float)matrix[3][2];
			return true;
		}
	}
	return false;
}

bool FbxParts::GetBonePosition(UINT num, XMFLOAT3* position)
{
	if(num>=boneNum_)
	return false;
	FbxAMatrix matrix;
	ppCluster_[num]->GetTransformLinkMatrix(matrix);
	position->x = (float)matrix[3][0];
	position->y = (float)matrix[3][1];
	position->z = (float)matrix[3][2];
	return true;
}

std::string FbxParts::GetBoneName(UINT num)
{
	if (num >= boneNum_)
		return "";
	return ppCluster_[num]->GetLink()->GetName();
}

void FbxParts::SetColor(int materialNum, const XMFLOAT4& color)
{
	if (materialNum >= materialCount_)
		materialNum = 0;
	materialList_[materialNum].SetCustomColor(color);
}

void FbxParts::RayCast(RayCastData& rayData, Transform& transform)
{

	for (int material = 0; material < materialCount_; material++)
	{
		XMVECTOR vDir = XMLoadFloat3(&rayData.dir);
		vDir = XMVector3Normalize(vDir);
		XMStoreFloat3(&rayData.dir, vDir);
		//float prev = 9999.0f;

		XMVECTOR nmlVec1;
		XMVECTOR nmlVec2;
		for (int poly = 0; poly < indexCount_.get()[material]; poly++)
		{
			//3つの頂点のベクトルを使って当たっているかどうかの判別をする
			XMFLOAT3 v0 = { 0,0,0 };
			XMStoreFloat3(&v0, pVertices_[ppIndex_[material][poly]].position);

			XMFLOAT3 v1 = { 0,0,0 };
			XMStoreFloat3(&v1, pVertices_[ppIndex_[material][poly + 1]].position);

			XMFLOAT3 v2 = { 0,0,0 };
			XMStoreFloat3(&v2, pVertices_[ppIndex_[material][poly + 2]].position);

			nmlVec1 = pVertices_[ppIndex_[material][poly + 1]].position - pVertices_[ppIndex_[material][poly]].position;
			nmlVec2 = pVertices_[ppIndex_[material][poly + 2]].position - pVertices_[ppIndex_[material][poly]].position;
			poly += 2;

			XMVECTOR hitPosition;
			float dist;
			XMVECTOR normal = XMVector3Normalize(XMVector3Cross(nmlVec1, nmlVec2));
			float angle = acosf(Clamp<float>(VectorDot(normal, -vDir),-1,1));
			if (Math::Intersect(rayData.start, rayData.dir, v0, v1, v2, dist, hitPosition) && dist < rayData.dist && dist < rayData.distLimit && Math::IsFrontSurface(normal, XMLoadFloat3(&rayData.dir)))
			{
				rayData.normal = normal;
				rayData.hitPos = XMVector3TransformCoord(hitPosition, transform.GetWorldMatrix());
				rayData.dist = dist;
				rayData.angle = angle;
				rayData.hit = true;
			}

		}
	}
}