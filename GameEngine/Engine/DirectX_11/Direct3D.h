#pragma once
#include <d3d11.h>
#include<assert.h>
#include"Math.h"
#include<vector>
#include"../SAFE_DELETE_RELEASE.h"
using namespace DirectX;

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum class SHADER_TYPE
{
	SHADER_2D = 0,
	SHADER_3D,
	SHADER_EFF,
	SHADER_OUTLINE,
	SHADER_TOON,
	SHADER_COLLIDER,
	SHADER_SKYBOX,
	SHADER_SHADOW,
	SHADER_MAX,
};
enum classTARGET
{
	TARGET_BACK_BUFFER=0,
	TARGET_RENDER_TARGET_1,
	TARGET_RENDER_TARGET_2,
	TARGET_RENDER_TARGET_3,
	TARGET_RENDER_TARGET_MAX
};

enum class BLEND_MODE
{
	BLEND_DEFAULT = 0,
	BLEND_ADD,
	BLEND_MAX
};


namespace Direct3D
{
	enum RENDER_TYPE
	{
		BACK_BUFFER = 0,
		RENDER_TARGET,
		RENDER_MAX
	};
	extern ID3D11Device* pDevice;				//�f�o�C�X
	extern ID3D11DeviceContext* pContext;		//�f�o�C�X�R���e�L�X�g
	

	//extern int screenWidth;
	//extern int screenHeight;
	

	//������
	HRESULT Initialize(int screenW, int screenH, HWND hWnd, XMINT2 windowSize = {1920,1080});
	HRESULT InitDepthTexture();
	//�V�F�[�_�[����
    HRESULT InitShader();
	HRESULT InitShader2D();
	HRESULT InitShader3D();
	HRESULT InitShaderEFF();
	HRESULT InitShaderOutLine();
	HRESULT InitShaderToon();
	HRESULT InitShaderCollider();
	HRESULT InitShaderSkyBox();
	HRESULT InitShaderShadow();




	void SetShader(SHADER_TYPE type);
	void SetBlendMode(BLEND_MODE mode);
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	IDXGISwapChain* GetSwapChain();
	void FullScreen(BOOL isFullScreen);
	int GetScreenWidth();
	int GetScreenHeight();
	void SetScreenWidth(int w);
	void SetScreenHeight(int h);
	XMINT2 GetDisplaySize();

	HWND GetWindowHandle(); 
	void SetDepthBufferWriteEnable(bool isWrite);
	int GetViewPortCount();
	void AddViewPort(D3D11_VIEWPORT port);
	void RemoveViewPort(UINT index);
	void SetViewPort(D3D11_VIEWPORT viewPort);
	int GetViewNumber();
	BOOL  SetClipCursor(const RECT& range = {-10000,0,0,0});
	const RECT& GetClipRect();
	void ShowMouseCursor(bool flag);
	bool GetShowMouseCursor();
	const XMINT2& GetWindwSize();
	void SetLightDirection(const XMFLOAT3& dir);
	const XMFLOAT4& GetLightDirection();
	ID3D11ShaderResourceView* GetDepthSRV();
	ID3D11SamplerState* GetDepthSampler();
	const XMMATRIX& GetLightViewMatrix();
	const XMMATRIX& GetLightProjectionMatrix();
	const XMMATRIX& GetClipToUVMatrix();

	void BeginDrawShadow();
	void EndDrawShadow();

	void SetLight(const XMFLOAT3& pos,const XMFLOAT3& targetPos);
	void SetLightClip(float nearClip, float farClip);
	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

	
};