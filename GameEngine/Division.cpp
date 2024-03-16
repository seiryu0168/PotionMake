#include "Division.h"
#include "DebugUI.h"
#include "Engine/Time.h"
#include "Engine/DirectX_11/Input.h"
#include "Engine/newSceneManager.h"
#include "Engine/GameObject/CameraManager.h"
#include "Engine/Components/Image.h"
#include "Engine/Components/Transform.h"
#include "Engine/DirectX_11/Direct3D.h"
#include "Engine/DirectX_11/Texture.h"
#include <memory>
#include <mutex>

namespace
{
	bool isLoad = false;

	std::unique_ptr<Texture> pTexture_;

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Transform transform_;

	struct CONSTANT_BUFFER
	{
		XMMATRIX matWorld;
		XMMATRIX matUVTrans;
		XMFLOAT4 color;
		XMFLOAT4 ChangeColor;
	};

	const struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	} vertices[] =
	{
		//1
		XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,0.0f,0.0f),	// �l�p�`�̒��_�i����j
		XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f,0.0f,0.0f,0.0f),	// �l�p�`�̒��_�i�E��j
		XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f,1.0f,0.0f,0.0f),	// �l�p�`�̒��_�i�E���j
		XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,1.0f,0.0f,0.0f),   // �l�p�`�̒��_�i�����j
	};
	static const int vertexNum_ = 4;

	static const int index[] = { 0,1,2, 0,2,3 };

	static const int indexNum_ = 6;

	static CONSTANT_BUFFER cb;

	std::mutex mtx_;

	//Image image_;
}

namespace Division
{
	void CreateVB();
	void CreateIB();
	void CreateCB();
	void Prepare();
	void Draw();
}

namespace Division
{
	void setLoad(bool load)
	{
		isLoad = load;
	}

	void threadMain()
	{
		std::lock_guard<std::mutex> lock(mtx_);
		//�Q�[���̏���
		Time::Update();
		Input::Update();

		newSceneManager::Update();
		newSceneManager::CheckRemoveObject();
	}

	void threadDraw()
	{
#ifdef _DEBUG
		DebugUI::StartImGui();
		DebugUI::Debug(/*(GameObject*)pRootJob->FindChild("SceneManager")*/);
		//DebugUI::Log();
		ImGui::Render();
#endif 
		CameraManager::Update();
		
		//�`�揈��
		Direct3D::BeginDraw();
		std::lock_guard<std::mutex> lock(mtx_);
		if (isLoad)
		{
			//image_.Draw();
			//Draw();
		}
		else
		{
				newSceneManager::Draw();
			//for (int i = 0; i < CameraManager::GetCameraCount(); i++)
			//{
			//	CameraManager::UpdateCameraNum(i);
			//	Direct3D::SetViewPort(CameraManager::GetCamera(i).GetViewPort());
			//
			//}
		}
#ifdef _DEBUG	
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
		Direct3D::EndDraw();
	}
	void Initialize()
	{
		CreateVB();
		CreateIB();
		CreateCB();

		pTexture_ = std::make_unique<Texture>();
		pTexture_->Load("Assets\\Image\\parrot.jpg");

		//image_.StaticLoad("Assets\\Image\\parrot.jpg");

		Prepare();
	}

	void Draw()
	{
		Direct3D::SetShader(SHADER_TYPE::SHADER_2D);
		Direct3D::SetBlendMode(BLEND_MODE::BLEND_DEFAULT);
		Direct3D::SetDepthBufferWriteEnable(false);


		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));					// �f�[�^��l�𑗂�

		ID3D11SamplerState* pSampler = pTexture_->GetSampler();
		Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);
		ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
		Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

		Direct3D::pContext->Unmap(pConstantBuffer_, 0);//�ĊJ

		//���_�o�b�t�@
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

		// �C���f�b�N�X�o�b�t�@�[���Z�b�g
		Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

		//�R���X�^���g�o�b�t�@
		Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p
		Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

		Direct3D::pContext->DrawIndexed(indexNum_, 0, 0);

		Direct3D::SetDepthBufferWriteEnable(true);
	}

	void Release()
	{
		SAFE_RELEASE(pConstantBuffer_);
		SAFE_RELEASE(pIndexBuffer_);
		SAFE_RELEASE(pVertexBuffer_);
	}

	void CreateVB()
	{
		D3D11_BUFFER_DESC bd_vertex{};
		bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex{};
		data_vertex.pSysMem = vertices;
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	}

	void CreateIB()
	{
		D3D11_BUFFER_DESC   bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * indexNum_;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData{};
		InitData.pSysMem = index;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	}

	void CreateCB()
	{
		D3D11_BUFFER_DESC cb{};
		cb.ByteWidth = sizeof(::CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		// �R���X�^���g�o�b�t�@�̍쐬
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	}
	void Prepare()
	{
		float rectX = (float)pTexture_->GetWidth();
		float rectY = (float)pTexture_->GetHeight();

		//��ʂ̃T�C�Y�ɍ��킹��s��
		XMMATRIX matImageSize = XMMatrixScaling((float)(1.0f / Direct3D::GetScreenWidth()), (float)(1.0f / Direct3D::GetScreenHeight()), 1.0f);
		//�؂蔲���T�C�Y�ɍ��킹��s��
		XMMATRIX matCut = XMMatrixScaling(rectX, rectY, 1.0f);


		//�ŏI�I�ȍs��
		cb.matWorld = XMMatrixTranspose(matCut * transform_.GetWorldScaleMatrix() * transform_.GetWorldRotateMatrix() * transform_.GetWorldTranslateMatrix());

		XMMATRIX matTexTrans = XMMatrixTranslation(0, 0, 1.0f);
		XMMATRIX matTexScale = XMMatrixScaling(1, 1, 1.0f);

		cb.color = XMFLOAT4(1, 1, 1, 1);
		cb.matUVTrans = XMMatrixTranspose(matTexScale * matTexTrans);
		cb.ChangeColor = { 0,0,0,0 };
	}
}

