#include <d3dcompiler.h>
#include"../../EngineTime.h"
#include "Direct3D.h"
#include<array>

//変数
namespace Direct3D
{
	ID3D11Device* pDevice;										//デバイス
	ID3D11DeviceContext* pContext;								//デバイスコンテキスト
	IDXGISwapChain* pSwapChain;									//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView;					//レンダーターゲットビュー
	ID3D11Texture2D* pDepthStencil;								//深度ステンシル
	ID3D11DepthStencilView* pDepthStencilView;									//深度ステンシルビュー
	ID3D11BlendState* pBlendState[(int)BLEND_MODE::BLEND_MAX];					//ブレンドステート
	ID3D11DepthStencilState* pDepthStencilState[(int)BLEND_MODE::BLEND_MAX];	//デプスステンシルステート
	HWND hWnd_;
	RECT* clipRect_ = nullptr;
	bool showCursorFlag_ = true;
	XMFLOAT4 lightDir_ = { 0,-1,0,0 };
	XMINT2 windowSize_ = {0,0};

	struct SHADER_BUNDLE
	{
		ID3D11VertexShader* pVertexShader = nullptr;	//頂点シェーダー
		ID3D11PixelShader* pPixelShader = nullptr;		//ピクセルシェーダー
		ID3D11InputLayout* pVertexLayout = nullptr;		//頂点インプットレイアウト
		ID3D11RasterizerState* pRasterizerState = nullptr;	//ラスタライザー
	};
	SHADER_BUNDLE shaderBundle[(int)SHADER_TYPE::SHADER_MAX];

	int screenWidth;
	int screenHeight;

	XMINT2 displaySize;

	D3D11_VIEWPORT vp;

	ID3D11Texture2D* pDepthTexture;			//描画先
	ID3D11RenderTargetView* pDepthRenderTargetView;	//レンダーターゲット
	ID3D11DepthStencilView* pDepthDepthStencilView;	//ステンシルバッファ
	ID3D11Texture2D* pDepthDepthStencil;		//深度バッファ用テクスチャ
	ID3D11ShaderResourceView* pDepthSRV;		//深度テクスチャをシェーダーに渡すやつ
	D3D11_VIEWPORT depthVp;

	ID3D11SamplerState* pDepthSampler;
	XMMATRIX clipToUVMatrix;
	XMMATRIX lightViewMatrix;
	XMMATRIX lightPrjMatrix_;

	std::vector<D3D11_VIEWPORT> viewPortList_;
	D3D11_VIEWPORT vp_01;
	D3D11_VIEWPORT vp_02;
	D3D11_VIEWPORT vp_03;
	D3D11_VIEWPORT vp_04;
	int viewNumber_ = 0;
}

//初期化
HRESULT Direct3D::Initialize(int screenW, int screenH, HWND hWnd, XMINT2 windowSize)
{
	hWnd_ = hWnd;
	RECT desctopSize;
	HWND desctopWnd=GetDesktopWindow();
	GetWindowRect(desctopWnd, &desctopSize);
	displaySize.x = desctopSize.right - desctopSize.left;
	displaySize.y = desctopSize.bottom - desctopSize.top;
	screenWidth = screenW;
	screenHeight = screenH;
	windowSize_ = windowSize;
	///////////////////////////いろいろ準備するための設定///////////////////////////////
	//いろいろな設定項目をまとめた構造体
	DXGI_SWAP_CHAIN_DESC scDesc;

	//とりあえず全部0
	ZeroMemory(&scDesc, sizeof(scDesc));

	//描画先のフォーマット
	scDesc.BufferDesc.Width = screenW;		//画面幅
	scDesc.BufferDesc.Height = screenH;	//画面高さ
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 何色使えるか

	//FPS（1/60秒に1回）
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;

	//その他
	scDesc.Windowed = TRUE;			//ウィンドウモードかフルスクリーンか
	scDesc.OutputWindow = hWnd;		//ウィンドウハンドル
	scDesc.BufferCount = 1;			//バックバッファの枚数
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//バックバッファの使い道＝画面に描画するために
	scDesc.SampleDesc.Count = 1;		//MSAA（アンチエイリアス）の設定
	scDesc.SampleDesc.Quality = 0;		//　〃

	////////////////上記設定をもとにデバイス、コンテキスト、スワップチェインを作成////////////////////////
	D3D_FEATURE_LEVEL level;
	D3D11CreateDeviceAndSwapChain(
		nullptr,						// どのビデオアダプタを使用するか？既定ならばnullptrで
		D3D_DRIVER_TYPE_HARDWARE,		// ドライバのタイプを渡す。ふつうはHARDWARE
		nullptr,						// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しないかぎりnullptr
		D3D10_CREATE_DEVICE_BGRA_SUPPORT,//D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT,								// 何らかのフラグを指定する。（デバッグ時はD3D11_CREATE_DEVICE_DEBUG？）
		nullptr,						// デバイス、コンテキストのレベルを設定。nullptrにしとけばOK
		0,								// 上の引数でレベルを何個指定したか
		D3D11_SDK_VERSION,				// SDKのバージョン。必ずこの値
		&scDesc,						// 上でいろいろ設定した構造体
		&pSwapChain,					// 無事完成したSwapChainのアドレスが返ってくる
		&pDevice,						// 無事完成したDeviceアドレスが返ってくる
		&level,							// 無事完成したDevice、Contextのレベルが返ってくる
		&pContext);						// 無事完成したContextのアドレスが返ってくる

	///////////////////////////レンダーターゲットビュー作成///////////////////////////////
	//スワップチェーンからバックバッファを取得（バックバッファ ＝ レンダーターゲット）

	//レンダーターゲットビューを作成
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	assert(pBackBuffer != nullptr);
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	//一時的にバックバッファを取得しただけなので解放
	SAFE_RELEASE(pBackBuffer);

	///////////////////////////ビューポート（描画範囲）設定///////////////////////////////
	//レンダリング結果を表示する範囲
	//vp.Width = (float)winW;	//幅
	//vp.Height = (float)winH;//高さ
	//vp.MinDepth = 0.0f;	//手前
	//vp.MaxDepth = 1.0f;	//奥
	//vp.TopLeftX = 0;	//左
	//vp.TopLeftY = 0;	//上

	//viewPortList_.push_back(vp);
	//vp_01.Width = (float)winW / 2;
	//vp_01.Height = (float)winH/2;
	//vp_01.MinDepth = 0.0f;
	//vp_01.MaxDepth = 1.0f;
	//vp_01.TopLeftX = 0;
	//vp_01.TopLeftY = 250;
	//
	//vp_02.Width = (float)winW / 2;
	//vp_02.Height = (float)winH/2;
	//vp_02.MinDepth = 0.0f;
	//vp_02.MaxDepth = 1.0f;
	//vp_02.TopLeftX = (float)winW / 2;
	//vp_02.TopLeftY = 250;

	//深度ステンシルビューの作成
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = screenW;
	descDepth.Height = screenH;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	pDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(pDepthStencil != nullptr);
	pDevice->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);


	//深度ステンシルステートの作成
	D3D11_DEPTH_STENCIL_DESC depthstencildesc = {};
	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthstencildesc.StencilEnable = true;

	pDevice->CreateDepthStencilState(&depthstencildesc, &pDepthStencilState[(int)BLEND_MODE::BLEND_DEFAULT]);
	pContext->OMSetDepthStencilState(pDepthStencilState[(int)BLEND_MODE::BLEND_DEFAULT], 0);

	depthstencildesc.StencilEnable = false;
	pDevice->CreateDepthStencilState(&depthstencildesc, &pDepthStencilState[(int)BLEND_MODE::BLEND_ADD]);

	//ブレンドステートの作成

	//デフォルト
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float factor[4] = { D3D11_BLEND_ZERO,D3D11_BLEND_ZERO ,D3D11_BLEND_ZERO ,D3D11_BLEND_ZERO };
	HRESULT hr;
	hr=pDevice->CreateBlendState(&desc, &pBlendState[(int)BLEND_MODE::BLEND_DEFAULT]);

	if(FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp:ブレンドステートの作成に失敗", L"エラー", MB_OK);
		return hr;
	}
	pContext->OMSetBlendState(pBlendState[(int)BLEND_MODE::BLEND_DEFAULT], factor, 0xffffffff);
	//加算合成
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	pDevice->CreateBlendState(&desc, &pBlendState[(int)BLEND_MODE::BLEND_ADD]);



	//データを画面に描画するための一通りの設定（パイプライン）
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);       //データの入力種類を指定
	pContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);// 描画先を設定
	//pContext->RSSetViewports(1, &vp);
	hr=InitDepthTexture();
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp:深度テクスチャの作成に失敗", L"エラー", MB_OK);
		return hr;
	}
	//シェーダー準備
	 hr=InitShader();
	 if (FAILED(hr))
	 {
		 return hr;
	 }

	 return S_OK;
}

HRESULT Direct3D::InitDepthTexture()
{
	HRESULT hr;
	//深度テクスチャの描画先作成
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	textureDesc.Width = screenWidth;
	textureDesc.Height = screenHeight;
	textureDesc.ArraySize = 1;
	textureDesc.MipLevels = 1;
	textureDesc.MiscFlags = 0;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	hr = pDevice->CreateTexture2D(&textureDesc, NULL, &pDepthTexture);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Direct3D::InitDepthTexture 深度テクスチャ作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//レンダーターゲットビュー作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	rtvDesc.Format = textureDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	hr = pDevice->CreateRenderTargetView(pDepthTexture, &rtvDesc, &pDepthRenderTargetView);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Direct3D::InitDepthTexture 深度テクスチャ用レンダーターゲットビュー作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthDesc.Width = screenWidth*2;
	depthDesc.Height = screenHeight*2;
	depthDesc.ArraySize = 1;
	depthDesc.MipLevels = 1;
	depthDesc.MiscFlags = 0;
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;

	hr = pDevice->CreateTexture2D(&depthDesc, NULL, &pDepthDepthStencil);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Direct3D::InitDepthTexture 深度テクスチャ用デプスステンシル作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	hr = pDevice->CreateDepthStencilView(pDepthDepthStencil, NULL, &pDepthDepthStencilView);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Direct3D::InitDepthTexture 深度テクスチャ用デプスステンシルビュー作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//深度テクスチャ用シェーダーリソースビュー作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	hr = pDevice->CreateShaderResourceView(pDepthTexture, &srvDesc, &pDepthSRV);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Direct3D::InitDepthTexture 深度テクスチャ用シェーダーリソースビュー作成に失敗", L"エラー", MB_OK);
		return hr;
	}
	XMFLOAT4X4 clip;
	ZeroMemory(&clip, sizeof(XMFLOAT4X4));
	clip = { 0.5,     0,   0,   0,
			   0,  -0.5,   0,   0,
			   0,     0, 1.0,   0,
			 0.5,   0.5,   0, 1.0 };

	clipToUVMatrix = XMLoadFloat4x4(&clip);

	depthVp.Width = (float)screenWidth;	//幅
	depthVp.Height = (float)screenHeight;//高さ
	depthVp.MinDepth = 0.0f;	//手前
	depthVp.MaxDepth = 1.0f;	//奥
	depthVp.TopLeftX = 0;	//左
	depthVp.TopLeftY = 0;	//上

	//深度テクスチャ用サンプラー作成
	D3D11_SAMPLER_DESC  depthSmplDesc;
	ZeroMemory(&depthSmplDesc, sizeof(D3D11_SAMPLER_DESC));
	depthSmplDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	depthSmplDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	depthSmplDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	depthSmplDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	lightViewMatrix = XMMatrixLookAtLH(XMVectorSet(0, 500, 10, 0),
		XMVectorSet(0, 0, 0, 0),
		XMVectorSet(0, 1, 0, 0));
	lightPrjMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)screenWidth / (FLOAT)screenHeight, 430, 600);

	hr = Direct3D::pDevice->CreateSamplerState(&depthSmplDesc, &pDepthSampler);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Direct3D::InitDepthTexture サンプラー作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

//シェーダー準備
HRESULT Direct3D::InitShader()
{	
	if (FAILED(InitShader2D()))
	{
		return E_FAIL;
	}
	if (FAILED(InitShader3D()))
	{
		return E_FAIL;
	}
	if(FAILED(InitShaderEFF()))
	{
		return E_FAIL;

	}
	if (FAILED(InitShaderOutLine()))
	{
		return E_FAIL;
	}
	if (FAILED(InitShaderToon()))
	{
		return E_FAIL;
	}
	if(FAILED(InitShaderCollider()))
	{
		return E_FAIL;
	}
	if (FAILED(InitShaderSkyBox()))
	{
		return E_FAIL;
	}
	if (FAILED(InitShaderShadow()))
	{
		return E_FAIL;
	}
	return S_OK;

}

HRESULT Direct3D::InitShader2D()
{
	HRESULT hr;
	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL,
									 &shaderBundle[(int)SHADER_TYPE::SHADER_2D].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader2D:頂点シェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//頂点インプットレイアウト   頂点シェーダ―に渡す情報
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(XMVECTOR),  D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV座標
	};
	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(),
									pCompileVS->GetBufferSize(), &shaderBundle[(int)SHADER_TYPE::SHADER_2D].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader2D:頂点インプットレイアウトの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL,
									&shaderBundle[(int)SHADER_TYPE::SHADER_2D].pPixelShader);

	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompilePS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader2D:ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompilePS);

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[(int)SHADER_TYPE::SHADER_2D].pRasterizerState);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompilePS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader2D:ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShader3D()
{
	HRESULT hr;
	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/newSimple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL,
									 &shaderBundle[(int)SHADER_TYPE::SHADER_3D].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader3D:頂点シェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//////////////////////////////////////////////////頂点インプットレイアウト///////////////////////////////////////////////
	//HLSL(シェーダーの事)に送る情報の種類とその設定を行う
	//1.セマンティックの名前
	//2.セマンティックインデックス(同じセマンティックを持つ要素が複数あるときに使う)
	//3.要素データのデータデータ型
	//4.入力アセンブラを識別する整数値(0〜15)
	//5.頂点の先頭アドレスからのオフセット(バイト単位)
	//6.入力スロットの入力データクラスの識別
	//7.バッファ内で1要素進む前に、同じインスタンスごとのデータを使用して
	//描画するインスタンスの数頂点単位のデータを含む要素の場合、0にする・・・らしい
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,				0,	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(XMVECTOR),	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV座標
		{ "NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //法線
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //接線
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(), 
									pCompileVS->GetBufferSize(), &shaderBundle[(int)SHADER_TYPE::SHADER_3D].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader3D:頂点インプットレイアウトの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/newSimple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL,
									&shaderBundle[(int)SHADER_TYPE::SHADER_3D].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader3D:ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[(int)SHADER_TYPE::SHADER_3D].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader3D:ラスタライザの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShaderEFF()
{
	HRESULT hr;
	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/BillBoard.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL,
									 &shaderBundle[(int)SHADER_TYPE::SHADER_EFF].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderEFF:頂点シェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/BillBoard.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL,
									&shaderBundle[(int)SHADER_TYPE::SHADER_EFF].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderEFF:ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//////////////////////////////////////////////////頂点インプットレイアウト///////////////////////////////////////////////
	//HLSL(シェーダーの事)に送る情報の種類とその設定を行う
	//1.セマンティックの名前
	//2.セマンティックインデックス(同じセマンティックを持つ要素が複数あるときに使う)
	//3.要素データのデータデータ型
	//4.入力アセンブラを識別する整数値(0〜15)
	//5.頂点の先頭アドレスからのオフセット(バイト単位)
	//6.入力スロットの入力データクラスの識別
	//7.バッファ内で1要素進む前に、同じインスタンスごとのデータを使用して
	//描画するインスタンスの数頂点単位のデータを含む要素の場合、0にする・・・らしい
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,					D3D11_INPUT_PER_VERTEX_DATA, 0 },  //位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	  0, sizeof(XMFLOAT3),  D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV座標
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(),
									pCompileVS->GetBufferSize(), &shaderBundle[(int)SHADER_TYPE::SHADER_EFF].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderEFF:頂点インプットレイアウトの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);


	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise =TRUE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[(int)SHADER_TYPE::SHADER_EFF].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderEFF:ラスタライザの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShaderOutLine()
{
	HRESULT hr;
	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/OutLine.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, 
									 &shaderBundle[(int)SHADER_TYPE::SHADER_OUTLINE].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderOutLine:頂点シェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//////////////////////////////////////////////////頂点インプットレイアウト///////////////////////////////////////////////
	//HLSL(シェーダーの事)に送る情報の種類とその設定を行う
	//1.セマンティックの名前
	//2.セマンティックインデックス(同じセマンティックを持つ要素が複数あるときに使う)
	//3.要素データのデータデータ型
	//4.入力アセンブラを識別する整数値(0〜15)
	//5.頂点の先頭アドレスからのオフセット(バイト単位)
	//6.入力スロットの入力データクラスの識別
	//7.バッファ内で1要素進む前に、同じインスタンスごとのデータを使用して
	//描画するインスタンスの数頂点単位のデータを含む要素の場合、0にする・・・らしい
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,				0,	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(XMVECTOR),	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV座標
		{ "NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //法線
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //接線
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(),
									pCompileVS->GetBufferSize(), &shaderBundle[(int)SHADER_TYPE::SHADER_OUTLINE].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderOutLine:頂点インプットレイアウトの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/OutLine.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL,
									&shaderBundle[(int)SHADER_TYPE::SHADER_OUTLINE].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderOutLine:ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_FRONT;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[(int)SHADER_TYPE::SHADER_OUTLINE].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderOutLine:ラスタライザの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShaderToon()
{
	HRESULT hr;
	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/ToonShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL,
									 &shaderBundle[(int)SHADER_TYPE::SHADER_TOON].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderToon:頂点シェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//////////////////////////////////////////////////頂点インプットレイアウト///////////////////////////////////////////////
	//HLSL(シェーダーの事)に送る情報の種類とその設定を行う
	//1.セマンティックの名前
	//2.セマンティックインデックス(同じセマンティックを持つ要素が複数あるときに使う)
	//3.要素データのデータデータ型
	//4.入力アセンブラを識別する整数値(0〜15)
	//5.頂点の先頭アドレスからのオフセット(バイト単位)
	//6.入力スロットの入力データクラスの識別
	//7.バッファ内で1要素進む前に、同じインスタンスごとのデータを使用して
	//描画するインスタンスの数頂点単位のデータを含む要素の場合、0にする・・・らしい
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,				0,	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(XMVECTOR),	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV座標
		{ "NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //法線
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //接線
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), 
									&shaderBundle[(int)SHADER_TYPE::SHADER_TOON].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderToon:頂点インプットレイアウトの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/ToonShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, 
									&shaderBundle[(int)SHADER_TYPE::SHADER_TOON].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderToon:ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[(int)SHADER_TYPE::SHADER_TOON].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderToon:ラスタライザの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShaderCollider()
{
	HRESULT hr;
	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/ColliderShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL,
		&shaderBundle[(int)SHADER_TYPE::SHADER_COLLIDER].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderCollider:頂点シェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//////////////////////////////////////////////////頂点インプットレイアウト///////////////////////////////////////////////
	//HLSL(シェーダーの事)に送る情報の種類とその設定を行う
	//1.セマンティックの名前
	//2.セマンティックインデックス(同じセマンティックを持つ要素が複数あるときに使う)
	//3.要素データのデータデータ型
	//4.入力アセンブラを識別する整数値(0〜15)
	//5.頂点の先頭アドレスからのオフセット(バイト単位)
	//6.入力スロットの入力データクラスの識別
	//7.バッファ内で1要素進む前に、同じインスタンスごとのデータを使用して
	//描画するインスタンスの数頂点単位のデータを含む要素の場合、0にする・・・らしい
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,				0,	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(XMVECTOR),	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV座標
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(),
		pCompileVS->GetBufferSize(), &shaderBundle[(int)SHADER_TYPE::SHADER_COLLIDER].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderCollider:頂点インプットレイアウトの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/ColliderShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL,
		&shaderBundle[(int)SHADER_TYPE::SHADER_COLLIDER].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderCollider:ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_WIREFRAME;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[(int)SHADER_TYPE::SHADER_COLLIDER].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderCollider:ラスタライザの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShaderSkyBox()
{
	HRESULT hr;
	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/SkyBoxShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL,
		&shaderBundle[(int)SHADER_TYPE::SHADER_SKYBOX].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderSkyBox:頂点シェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//////////////////////////////////////////////////頂点インプットレイアウト///////////////////////////////////////////////
	//HLSL(シェーダーの事)に送る情報の種類とその設定を行う
	//1.セマンティックの名前
	//2.セマンティックインデックス(同じセマンティックを持つ要素が複数あるときに使う)
	//3.要素データのデータデータ型
	//4.入力アセンブラを識別する整数値(0〜15)
	//5.頂点の先頭アドレスからのオフセット(バイト単位)
	//6.入力スロットの入力データクラスの識別
	//7.バッファ内で1要素進む前に、同じインスタンスごとのデータを使用して
	//描画するインスタンスの数頂点単位のデータを含む要素の場合、0にする・・・らしい
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,				0,	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(XMVECTOR),	   D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV座標
		{ "NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //法線
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(),
		pCompileVS->GetBufferSize(), &shaderBundle[(int)SHADER_TYPE::SHADER_SKYBOX].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderSkyBox:頂点インプットレイアウトの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/SkyBoxShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL,
		&shaderBundle[(int)SHADER_TYPE::SHADER_SKYBOX].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShaderSkyBox:ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[(int)SHADER_TYPE::SHADER_SKYBOX].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct3D.cpp InitShader3D:ラスタライザの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShaderShadow()
{
	HRESULT hr;
	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	ID3DBlob* pVSError = nullptr;
	hr = D3DCompileFromFile(L"Assets/HLSL/DepthShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, &pVSError);
	assert(pCompileVS != nullptr);
	if (FAILED(hr))
	{
		if (pVSError != nullptr)
		{
			MessageBox(nullptr, (LPCWSTR)pVSError->GetBufferPointer(), L"エラー", MB_OK);
		}

		SAFE_RELEASE(pVSError);
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"頂点シェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pVSError);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL,
		&shaderBundle[(int)SHADER_TYPE::SHADER_SHADOW].pVertexShader);

	//////////////////////////////////////////////////頂点インプットレイアウト///////////////////////////////////////////////
	//HLSL(シェーダーのソースコード)に送る情報の種類とその設定を行う
	//1.セマンティックの名前
	//2.セマンティックインデックス(同じセマンティックを持つ要素が複数あるときに使う)
	//3.要素データのデータデータ型
	//4.入力アセンブラを識別する整数値(0〜15)
	//5.頂点の先頭アドレスからのオフセット(バイト単位)
	//6.入力スロットの入力データクラスの識別
	//7.バッファ内で1要素進む前に、同じインスタンスごとのデータを使用して
	//描画するインスタンスの数頂点単位のデータを含む要素の場合、0にする・・・らしい
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //位置
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(),
		pCompileVS->GetBufferSize(), &shaderBundle[(int)SHADER_TYPE::SHADER_SHADOW].pVertexLayout);
	if (FAILED(hr))
	{

		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"頂点インプットレイアウトの設定に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	ID3DBlob* pPSError = nullptr;
	D3DCompileFromFile(L"Assets/HLSL/DepthShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, &pPSError);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL,
		&shaderBundle[(int)SHADER_TYPE::SHADER_SHADOW].pPixelShader);

	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		if (pPSError != nullptr)
		{
			MessageBox(nullptr, (LPCWSTR)pPSError->GetBufferPointer(), L"エラー", MB_OK);
		}
		SAFE_RELEASE(pPSError);
		MessageBox(nullptr, L"ピクセルシェーダの作成に失敗", L"エラー", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pPSError);

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[(int)SHADER_TYPE::SHADER_SHADOW].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"ラスタライザの作成に失敗", L"エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

void Direct3D::SetShader(SHADER_TYPE type)
{
	//それぞれをデバイスコンテキストにセット  これらの情報を使って描画を行う
	pContext->VSSetShader(shaderBundle[(int)type].pVertexShader, NULL, 0);	//頂点シェーダー
	pContext->PSSetShader(shaderBundle[(int)type].pPixelShader, NULL, 0);	//ピクセルシェーダー
	pContext->IASetInputLayout(shaderBundle[(int)type].pVertexLayout);	//頂点インプットレイアウト
	pContext->RSSetState(shaderBundle[(int)type].pRasterizerState);		//ラスタライザー
}

void Direct3D::SetBlendMode(BLEND_MODE mode)
{
	float factor[4] = { D3D11_BLEND_ZERO,D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	Direct3D::pContext->OMSetBlendState(pBlendState[(int)mode], factor, 0xffffffff);			//ブレンドステート

	pContext->OMSetDepthStencilState(pDepthStencilState[(int)mode], 0);
}
ID3D11Device* Direct3D::GetDevice()
{
	return pDevice;
}

ID3D11DeviceContext* Direct3D::GetContext()
{
	 return pContext;
}
IDXGISwapChain* Direct3D::GetSwapChain()
{
	return pSwapChain;
}
void Direct3D::FullScreen(BOOL isFullScreen)
{
	pSwapChain->SetFullscreenState(isFullScreen, NULL);
}
int Direct3D::GetScreenWidth()
{
	return screenWidth;
}
int Direct3D::GetScreenHeight()
{
	return screenHeight;
}
void Direct3D::SetScreenWidth(int w)
{
	screenWidth = w;
}
void Direct3D::SetScreenHeight(int h)
{
	screenHeight = h;
}

XMINT2 Direct3D::GetDisplaySize()
{
	return displaySize;
}

HWND Direct3D::GetWindowHandle()
{
	return hWnd_;
}
void Direct3D::SetDepthBufferWriteEnable(bool isWrite)
{
	if (isWrite)
	{
		pContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);
	}

	else
	{
		pContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
	}
}

int Direct3D::GetViewPortCount()
{
	return (int)viewPortList_.size();
}
void Direct3D::AddViewPort(D3D11_VIEWPORT port)
{
	viewPortList_.push_back(port);
}
void Direct3D::RemoveViewPort(UINT index)
{
	//if(index<viewPortList_.size())
}
void Direct3D::SetViewPort(D3D11_VIEWPORT viewPort)
{
	pContext->RSSetViewports(1, &viewPort);
	//switch (num)
	//{
	//case 0:
	//	pContext->RSSetViewports(1, &vp_01);
	//	viewNumber_ = num;
	//	break;
	//case 1:
	//	pContext->RSSetViewports(1, &vp_02);
	//	viewNumber_ = num;
	//	break;
	//default:
	//	break;
	//}
}
int Direct3D::GetViewNumber()
{
	return viewNumber_;
}
BOOL Direct3D::SetClipCursor(const RECT& range)
{
	
	if (range.left == -10000)
	{
		delete clipRect_;
		clipRect_ = nullptr;
	}
	else
	{
		if (clipRect_ == nullptr)
			clipRect_ = new RECT;
		clipRect_->left = range.left;
		clipRect_->top = range.top;
		clipRect_->right = range.right;
		clipRect_->bottom = range.bottom;
	}
	return ClipCursor(clipRect_);
}
const RECT& Direct3D::GetClipRect()
{
	return *clipRect_;
	// TODO: return ステートメントをここに挿入します
}
void Direct3D::ShowMouseCursor(bool flag)
{
	if (flag)
	{
		do
		{
		} while (ShowCursor(flag) < 0);

	}
	else
	{
		do
		{
		} while (ShowCursor(flag)>= 0);
	}
	showCursorFlag_ = flag;
}
bool Direct3D::GetShowMouseCursor()
{
	return showCursorFlag_;
}
const XMINT2& Direct3D::GetWindwSize()
{
	return windowSize_;
}
void Direct3D::SetLightDirection(const XMFLOAT3& dir)
{
	lightDir_ = { dir.x,dir.y,dir.z,0 };
}
const XMFLOAT4& Direct3D::GetLightDirection()
{
	return lightDir_;
}
ID3D11ShaderResourceView* Direct3D::GetDepthSRV()
{
	return pDepthSRV;
}
ID3D11SamplerState* Direct3D::GetDepthSampler()
{
	return pDepthSampler;
}
const XMMATRIX& Direct3D::GetLightViewMatrix()
{
	return lightViewMatrix;
}
const XMMATRIX& Direct3D::GetLightProjectionMatrix()
{
	return lightPrjMatrix_;
}
const XMMATRIX& Direct3D::GetClipToUVMatrix()
{
	return clipToUVMatrix;
}
void Direct3D::BeginDrawShadow()
{
	float color[4] = { 0,0,0,0 };
	pContext->OMSetRenderTargets(1, &pDepthRenderTargetView, pDepthDepthStencilView);
	pContext->ClearRenderTargetView(pDepthRenderTargetView, color);
	pContext->ClearDepthStencilView(pDepthDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	pContext->RSSetViewports(1, &depthVp);

}
void Direct3D::EndDrawShadow()
{
	pContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);
}
void Direct3D::SetLight(const XMFLOAT3& pos, const XMFLOAT3& targetPos)
{
	lightViewMatrix = XMMatrixLookAtLH(XMVectorSet(pos.x,pos.y,pos.z, 0),
								       XMVectorSet(targetPos.x, targetPos.y, targetPos.z, 0),
								       XMVectorSet(0, 1, 0, 0));
}
void Direct3D::SetLightClip(float nearClip, float farClip)
{
	lightPrjMatrix_= XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)screenWidth / (FLOAT)screenHeight, nearClip, farClip);
}
//描画開始
void Direct3D::BeginDraw()
{
	EngineTime::SetTime();
	//画面をクリア
		//背景色
		float clearColor[4] = { 0.1f,0.5f,0.5f,1.0f };
		//レンダーターゲットビューをクリア
		pContext->ClearRenderTargetView(pRenderTargetView, clearColor);

	//深度バッファクリア
	pContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//描画終了
void Direct3D::EndDraw()
{
	EngineTime::SetTime();
	//スワップ（バックバッファを表に表示する）
	HRESULT hr = pSwapChain->Present(0, 0);
	if (hr== DXGI_ERROR_DEVICE_REMOVED || hr== DXGI_ERROR_DEVICE_RESET)
	{
		
			MessageBox(nullptr, L"DirectX_11/Direct3D.cpp:スワップチェイン失敗", L"エラー", MB_OK);
		
	}
}

//解放処理
void Direct3D::Release()
{
	if (clipRect_ != nullptr)
	{
		ClipCursor(NULL);
		delete clipRect_;
	}

	//解放処理
	for (int releaseShader = 0; releaseShader < (int)SHADER_TYPE::SHADER_MAX; releaseShader++)
	{
		SAFE_RELEASE(shaderBundle[releaseShader].pRasterizerState);
		SAFE_RELEASE(shaderBundle[releaseShader].pVertexLayout);
		SAFE_RELEASE(shaderBundle[releaseShader].pPixelShader);
		SAFE_RELEASE(shaderBundle[releaseShader].pVertexShader);
	}

	for (int i = 0; i < (int)BLEND_MODE::BLEND_MAX; i++)
	{
		SAFE_RELEASE(pDepthStencilState[i]);
		SAFE_RELEASE(pBlendState[i]);				//深度ステンシル
	}
	SAFE_RELEASE(pDepthDepthStencilView);
	SAFE_RELEASE(pDepthDepthStencil);
	SAFE_RELEASE(pDepthRenderTargetView);
	SAFE_RELEASE(pDepthSRV);
	SAFE_RELEASE(pDepthSampler);

	SAFE_RELEASE(pDepthStencilView);				//深度ステンシルビュー
	SAFE_RELEASE(pDepthStencil);
	SAFE_RELEASE(pRenderTargetView);
	SAFE_RELEASE(pSwapChain);		//スワップチェイン
	SAFE_RELEASE(pContext);			//デバイスコンテキスト
	SAFE_RELEASE(pDevice);			//デバイス
}