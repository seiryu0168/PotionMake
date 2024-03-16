#include "LineParticle.h"
#include"../ResourceManager/TextureManager.h"
#include"../GameObject/CameraManager.h"
#include<vector>
LineParticle::LineParticle() : LineParticle(nullptr)
{
	blendMode_ = BLEND_MODE::BLEND_ADD;
}
LineParticle::LineParticle(GameObject* object,int layerNum)
	:attachObject_(object),
	WIDTH_(0.5),
	LENGTH_(2),
	endWidth_(0),
	color_({ 1,1,1,1 }),
	blendMode_(BLEND_MODE::BLEND_ADD),
	pVertexBuffer_(nullptr),
	pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),
	pTexture_(nullptr),
	layerNum_(layerNum)
{
	assert(LENGTH_ >= 1);
	endWidth_ = max(endWidth_, 0);
}

//���݈ʒu���L�� : pos
void LineParticle::AddPosition(const XMFLOAT3& pos)
{
	//���X�g�̐�[�Ɍ��݈ʒu������
	positionList_.push_front(pos);
	
	//LENGTH�����Ă���I�[��position���폜
	if (positionList_.size() > (size_t)LENGTH_+2)
	{
		positionList_.pop_back();
	}

	//���_�o�b�t�@���
	SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	indexList.clear();
	SetIndex();

	//�J�����̈ʒu�擾(�x�N�g����)
	XMFLOAT3 camPos = CameraManager::GetCurrentCamera().GetPosition();
	XMVECTOR vCamPos = XMLoadFloat3(&camPos);

	CreateMeshPype(&positionList_);
}

HRESULT LineParticle::CreateMeshPype(const std::list<XMFLOAT3>* pList)
{
	//�J�����̈ʒu�擾(�x�N�g����)
	XMFLOAT3 camPos = CameraManager::GetCurrentCamera().GetPosition();
	XMVECTOR vCamPos = XMLoadFloat3(&camPos);


	//���_�f�[�^�쐬
	XMVECTOR upVec = XMVectorSet(0, 1, 0, 0);
	std::vector<VERTEX> vertices;
	vertices.reserve(pList->size() * 4);

	int index = 0;
	auto itr = pList->begin();
	for (UINT j = 0; j < LENGTH_ + 2; j++)
	{
		//�L�����Ă���ʒu�擾
		XMVECTOR vPos = XMLoadFloat3(&(*itr));

		if (++itr == pList->end())
		{
			break;
		}

		//�������擾�����ʒu���玟�̈ʒu�Ɍ������x�N�g��
		XMVECTOR vLine = XMLoadFloat3(&(*itr)) - vPos;

		//�ړ��ʂ�0.01�ȏゾ������
		if (XMVectorGetX(XMVector3Length(vLine)) >= 0.01f)
		{
			//�p�[�e�B�N���̘r���񂷃N�I�[�^�j�I��
			XMVECTOR armRotate = XMQuaternionRotationAxis(vLine, (float)(std::numbers::pi_v<float> / 2.0f));

			//�p�[�e�B�N���̘r�����
			XMVECTOR vArm = XMVector3Cross(vLine, vCamPos);

			//�����ɂ���đ����ς��
			vArm = XMVector3Normalize(vArm) * (float)(WIDTH_ * (LENGTH_ - j) / LENGTH_);

			//�r����]
			XMVECTOR vArm2 = XMVector3Rotate(vArm, armRotate);
			XMFLOAT3 pos;

			//�Ђ��`�ɂȂ�悤�ɒ��_��z�u
			XMStoreFloat3(&pos, vPos + -vArm);
			VERTEX vertex0 = { pos,XMFLOAT3((float)j / LENGTH_,1.0f / 4.0f,0) };

			XMStoreFloat3(&pos, vPos + vArm2);
			VERTEX vertex1 = { pos,XMFLOAT3((float)j / LENGTH_,2.0f / 4.0f,0) };

			XMStoreFloat3(&pos, vPos + vArm);
			VERTEX vertex2 = { pos,XMFLOAT3((float)j / LENGTH_,3.0f / 4.0f,0) };

			XMStoreFloat3(&pos, vPos + -vArm2);
			VERTEX vertex3 = { pos,XMFLOAT3((float)j / LENGTH_,1,0) };

			vertices.push_back(vertex0);
			vertices.push_back(vertex1);
			vertices.push_back(vertex2);
			vertices.push_back(vertex3);
		}
		//������0.01�ȉ���������_�~�[�Ŗ��߂�
		else
		{
			XMFLOAT3 dumPos;
			XMStoreFloat3(&dumPos, vPos);
			VERTEX dummy = { dumPos,{0,0,0} };
			vertices.push_back(dummy);
			vertices.push_back(dummy);
			vertices.push_back(dummy);
			vertices.push_back(dummy);
		}
	}

#ifdef _DEBUG

	for (int i = 0; i < vertices.size() / sizeof(VERTEX); i++)
	{
		if (abs(vertices[i].position.x) <= 0.1f && abs(vertices[i].position.y) <= 1.1f && abs(vertices[i].position.z) <= 0.1f)
		{
			int a = 0;
		}
	}
#endif // _DEBUG

	//���_�����o�b�t�@�ɓ���鎞�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * (UINT)pList->size() * 4;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;

	//�o�b�t�@�ɓ����f�[�^
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices.data();

	//�o�b�t�@�ɓ����
	HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���C���p�[�e�B�N���̃|�W�V�����X�V���s", L"�G���[", MB_OK);
		return hr;
	}
	hr = Direct3D::pDevice->GetDeviceRemovedReason();
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���C���p�[�e�B�N���̃|�W�V�����X�V���s", L"�G���[", MB_OK);
		return hr;
	}

	return hr;
}

HRESULT LineParticle::CreateMeshPlate(const std::list<XMFLOAT3>* pList)
{
	//�J�����̈ʒu�擾(�x�N�g����)
	XMFLOAT3 camPos = CameraManager::GetCurrentCamera().GetPosition();
	XMVECTOR vCamPos = XMLoadFloat3(&camPos);

	auto itr = pList->begin();
	//���_�f�[�^�쐬
	std::vector<VERTEX> vertices;
	vertices.reserve(pList->size() * 2);

	for (UINT i = 0; i < LENGTH_ + 2; i++)
	{
		//�L�����Ă���ʒu�擾
		XMVECTOR vPos = XMLoadFloat3(&(*itr));

		if (++itr == pList->end())
		{
			break;
		}

		//�������擾�����ʒu���玟�̈ʒu�Ɍ������x�N�g��
		XMVECTOR vLine = XMLoadFloat3(&(*itr)) - vPos;

		XMVECTOR vArm = XMVector3Cross(vLine, vCamPos);
		vArm = XMVector3Normalize(vArm) * WIDTH_;

		XMFLOAT3 pos;
		XMStoreFloat3(&pos, vPos + vArm);
		VERTEX vertex1 = { pos,XMFLOAT3((float)i / LENGTH_ + endWidth_,0,0) };

		XMStoreFloat3(&pos, vPos - vArm);
		VERTEX vertex2 = { pos,XMFLOAT3((float)i / LENGTH_ + endWidth_,1,0) };

		vertices.push_back(vertex1);
		vertices.push_back(vertex2);
	}
	//���_�o�b�t�@�p��
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * ((size_t)LENGTH_ + 2) * 4;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = &vertices;
	HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);//���܂ɗ�O�̃X���[���N����B�����s��
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���C���p�[�e�B�N���̃|�W�V�����X�V���s", L"�G���[", MB_OK);
		return hr;
	}
	hr = Direct3D::pDevice->GetDeviceRemovedReason();

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���C���p�[�e�B�N���̃|�W�V�����X�V���s", L"�G���[", MB_OK);
		return hr;
	}

	return hr;
}

HRESULT LineParticle::Load(const std::string& fileName)
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd_constant;
	bd_constant.ByteWidth = sizeof(CONSTANT_BUFFER);
	bd_constant.Usage = D3D11_USAGE_DYNAMIC;
	bd_constant.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd_constant.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd_constant.MiscFlags = 0;
	bd_constant.StructureByteStride = 0;



	hr = Direct3D::pDevice->CreateBuffer(&bd_constant, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���C���p�[�e�B�N���p�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	pTexture_ = std::make_shared<Texture>();
	//wchar_t name[FILENAME_MAX];
	//size_t ret;
	//mbstowcs_s(&ret, name, fileName.c_str(), fileName.length());

	hr = pTexture_->Load(fileName.c_str());
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���C���p�[�e�B�N���̃e�N�X�`���̃��[�h�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	SetIndex();
	return S_OK;
}

void LineParticle::SetColor(const XMFLOAT4& col)
{
	color_ = col;
}

void LineParticle::SetIndex()
{
	//�C���f�b�N�X�̏����z��
	static int fixedIndex[] = { 0,0,-3, 3,-1,1, 5,5,2,  8, 4, 6, 10,10, 7, 13,9, 11, 15,19,16, 18,18,16 };

	//�z����ꏄ�������ɑ�����l
	int indexOffset = 0;
	int indexdelta = 1;
	
	//�C���f�b�N�X����
	for (UINT i = 0; i < LENGTH_*3*8; i++)
	{
			indexList.push_back(i - (indexOffset + fixedIndex[i % 24]));
		if (i%(24*indexdelta-1) == 0&&i!=0)
		{
			indexOffset += 20;
			indexdelta++;
		}
	}

	//�C���f�b�N�X�̃f�[�^
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = (int)(sizeof(int) * indexList.size());
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	//�z�񕔕�����Ă���ɂ�.data()�B&vector[0]�Ɠ��l
	InitData.pSysMem = indexList.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	//�C���f�b�N�X�o�b�t�@����
	HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		//return hr;
	}
	//return S_OK;
}

void LineParticle::Update()
{
	AddPosition(StoreFloat3(attachObject_->GetTransform()->position_));
}

void LineParticle::Draw()
{
	//Update();
	HRESULT hr;
	Direct3D::SetShader(SHADER_TYPE::SHADER_EFF);
	Direct3D::SetBlendMode(blendMode_);
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(CameraManager::GetCurrentCamera().GetViewMatrix() * CameraManager::GetCurrentCamera().GetProjectionMatrix());
	cb.color = color_;

	D3D11_MAPPED_SUBRESOURCE pdata;

	//GPU����̃f�[�^�A�N�Z�X���~�߂�
	hr = Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�f�o�C�X�R���e�L�X�g���s", L"�G���[", MB_OK);
	}
	//�f�[�^�𑗂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
	
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	//�f�[�^�A�N�Z�X�ĊJ
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	//���_�o�b�t�@
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
	
	//�C���f�b�N�X�o�b�t�@
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);
	
	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);//���_�V�F�[�_�[�p
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);//�s�N�Z���V�F�[�_�[�p

	//���_�̕��ѕ����w��
	Direct3D::pContext->DrawIndexed((UINT)indexList.size()-24,0,0);
	Direct3D::pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void LineParticle::Draw(int layerNum)
{
	if (layerNum != layerNum_)
		return;

	HRESULT hr;
	Direct3D::SetShader(SHADER_TYPE::SHADER_EFF);
	Direct3D::SetBlendMode(blendMode_);
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(CameraManager::GetCurrentCamera().GetViewMatrix() * CameraManager::GetCurrentCamera().GetProjectionMatrix());
	cb.color = color_;

	D3D11_MAPPED_SUBRESOURCE pdata;

	//GPU����̃f�[�^�A�N�Z�X���~�߂�
	hr = Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�f�o�C�X�R���e�L�X�g���s", L"�G���[", MB_OK);
	}
	//�f�[�^�𑗂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	//�f�[�^�A�N�Z�X�ĊJ
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	//���_�o�b�t�@
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	//�C���f�b�N�X�o�b�t�@
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);//���_�V�F�[�_�[�p
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);//�s�N�Z���V�F�[�_�[�p

	//���_�̕��ѕ����w��
	Direct3D::pContext->DrawIndexed((UINT)indexList.size() - 24, 0, 0);
	Direct3D::pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void LineParticle::SetLineParameter(const LineData& data)
{
	
	WIDTH_ = data.width;
	LENGTH_ = data.length;
	endWidth_ = data.endWidth;
	//pTexture_ = TextureManager::GetTexture(texNum);
	endWidth_ = max(endWidth_, 0);
	Load(data.textureName);
	
}

void LineParticle::DeleteLine()
{
	positionList_.clear();
}

void LineParticle::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	positionList_.clear();
}
