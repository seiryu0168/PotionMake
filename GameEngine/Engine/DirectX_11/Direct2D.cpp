#include "Direct2D.h"
#include"../SAFE_DELETE_RELEASE.h"
#include<fileSystem>
#include<vector>

namespace D2D
{
	ID2D1Factory*			pFactory_	     = nullptr;	//ファクトリ
	IDWriteFactory5*		pWriteFactory_   = nullptr;	//ライトファクトリ
	IDWriteFontSetBuilder1* pFontSetBuilder_ = nullptr;
	IDWriteFontCollection*  pSystemFontCollection_ = nullptr;
	IDWriteFontSet*			pFontSet_		 = nullptr;
	IDWriteFontCollection1* pFontCollection_ = nullptr;
	std::vector<ID2D1RenderTarget*>	renderTargets_; //レンダーターゲット
	std::vector<IDWriteFontFile*> fontFileList;
	//ID2D1SolidColorBrush*  pColorBrush_   = nullptr;	//ブラシ	
	//IDWriteFactory*		   pWriteFactory_ = nullptr;	//文字描画のファクトリ
	//IDWriteTextFormat*	   pTextFormat_   = nullptr;	//テキストフォーマット
	//const wchar_t*		   pWszText       = nullptr;	//テキスト
	UINT32				   textLength_	  = 0;
	D2D1_RECT_F			   layoutRect_;
	float				   dpiScaleX_;
	float				   dpiScaleY_;
	XMINT2 windowSize_ = {0,0};
}

HRESULT D2D::Initialize(int screenW, int screenH, HWND hWnd, XMINT2 windowSize)
{
	windowSize_ = windowSize;
	HRESULT hr;
	hr= D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct2D.cpp:ファクトリの作成に失敗", L"エラー", MB_OK);
		return hr;
	}
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pWriteFactory_));
	assert(FAILED(hr) == false);
	pWriteFactory_->GetSystemFontCollection(&pSystemFontCollection_);
	hr = pWriteFactory_->CreateFontSetBuilder(&pFontSetBuilder_);
	assert(FAILED(hr) == false);
	CreateFontCollection();

	IDXGISurface* pBackBuffer;	
	Direct3D::GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	
	RECT rect;
	GetClientRect(hWnd, &rect);
	
	//dpiScaleX_ = (float)GetDpiForWindow(hWnd)*((float)Direct3D::GetDisplaySize().x/(float)Direct3D::GetScreenWidth());
	//dpiScaleY_ = (float)GetDpiForWindow(hWnd) * ((float)Direct3D::GetDisplaySize().y/(float)Direct3D::GetScreenHeight());
	UINT X = GetDpiForWindow(hWnd);

	dpiScaleX_ = (float)GetDpiForWindow(hWnd) * ((float)Direct3D::GetScreenWidth()/ (float)Direct3D::GetDisplaySize().x );
	dpiScaleY_ = (float)GetDpiForWindow(hWnd) * ( (float)Direct3D::GetScreenHeight()/(float)Direct3D::GetDisplaySize().y);

	return S_OK;
}

HRESULT D2D::CreateFontCollection()
{
	//std::filesystem::recursive_directory_iterator rcsv_Directory_Itr("Assets/Font");

	//std::filesystem::path path = "Assets/Font/holiday_mdjp05/HolidayMDJP.otf";
	HRESULT hr;
	for (const std::filesystem::directory_entry& directry : std::filesystem::recursive_directory_iterator("Assets/Fonts"))
	{


		IDWriteFontFile* fontFile = nullptr;
		std::filesystem::path path = directry.path();
		std::string exname = path.extension().string();
		if (exname !=".ttf"&& exname !=".otf")
		{	
			SAFE_RELEASE(fontFile);
			continue;
		}
		hr = pWriteFactory_->CreateFontFileReference(directry.path().wstring().c_str(), nullptr, &fontFile);

		BOOL isFont;
		hr = fontFile->Analyze(&isFont, nullptr, nullptr, nullptr);
		if (isFont)
		{
			SAFE_RELEASE(fontFile);
		}
		else
		{
			hr = pFontSetBuilder_->AddFontFile(fontFile);
			assert(FAILED(hr) == false);
			fontFileList.push_back(fontFile);
		}

	}

		hr = pFontSetBuilder_->CreateFontSet(&pFontSet_);
		assert(FAILED(hr) == false);

		hr = pWriteFactory_->CreateFontCollectionFromFontSet(pFontSet_, &pFontCollection_);
		assert(FAILED(hr) == false);
	return hr;
}

IDWriteFontCollection* D2D::GetSystemFontCollection()
{
	return pSystemFontCollection_;
}

ID2D1Factory* D2D::Get2DFactory()
{
	return pFactory_;
}

IDWriteFactory5* D2D::GetDWriteFactory()
{
	return pWriteFactory_;
}

IDWriteFontCollection1* D2D::GetCollection()
{
	return pFontCollection_;
}
void D2D::CreateRenderTarget(const XMINT2 dpiScale, D2D1_RENDER_TARGET_TYPE type, DXGI_FORMAT format, D2D1_ALPHA_MODE mode)
{
	HRESULT hr;
	IDXGISurface* pBackBuffer;
	Direct3D::GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	D2D1_RENDER_TARGET_PROPERTIES prop = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiScaleX_, dpiScaleY_);
	ID2D1RenderTarget* pRenderTarget = nullptr;
	hr = pFactory_->CreateDxgiSurfaceRenderTarget(pBackBuffer, prop, &pRenderTarget);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"DirectX_11/Direct2D.cpp:レンダーターゲットの作成に失敗", L"エラー", MB_OK);
		return;
	}
	renderTargets_.push_back(pRenderTarget);
}
const int& D2D::GetRenderTargetCount()
{
	return renderTargets_.size();
}
ID2D1RenderTarget* D2D::GetRenderTarget(int num)
{
	return renderTargets_[num];
}
void D2D::AllRemoveRenderTarget()
{
	for (auto target : renderTargets_)
		SAFE_RELEASE(target);
	renderTargets_.clear();

}
void D2D::Release()
{
	SAFE_RELEASE(pFactory_);
	for(auto target : renderTargets_)
	SAFE_RELEASE(target);
	renderTargets_.clear();
}

void D2D::RenderTest()
{
	//HRESULT hr;
	//ID2D1SolidColorBrush* pGreenBrush=nullptr;
	//
	//hr = pRenderTarget_->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0.0f), &pGreenBrush);
	//if (FAILED(hr))
	//{
	//	MessageBox(nullptr, L"Direct2D : テスト失敗", L"エラー", MB_OK);
	//	//return hr;
	//}
	
	//D2D1_ELLIPSE ell = D2D1::Ellipse(D2D1::Point2F(1120.0f, 120.0f), 100.0f, 100.0f);
	//pRenderTarget_->DrawEllipse(ell, pGreenBrush, 10.0f);

	


	//SAFE_RELEASE(pGreenBrush);
}

void D2D::BeginDraw()
{
	//pRenderTarget_->Clear();
	//pRenderTarget_->BeginDraw();
}

//void D2D::Draw()
//{
//	pRenderTarget_->BeginDraw();
//	pRenderTarget_->SetTransform(D2D1::IdentityMatrix());	
//	pRenderTarget_->DrawTextW(pWszText, textLength_, pTextFormat_, layoutRect_, pColorBrush_);
//}

void D2D::EndDraw()
{
	//pRenderTarget_->EndDraw();
}

int D2D::GetdpiX()
{
	return (int)dpiScaleX_;
}

int D2D::GetdpiY()
{
	return (int)dpiScaleY_;
}

const XMINT2& D2D::GetWindowSize()
{
	return windowSize_;
}
