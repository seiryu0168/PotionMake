#pragma once
#include"../DirectX_11/Direct3D.h"
#include<d2d1.h>
#include<dwrite_3.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib,"dwrite.lib")
enum ALIGNMENT_TYPE
{
	LEFT_TOP = 0,
	LEFT_CENTER,
	LEFT_BOTTOM,
	CENTER_TOP,
	CENTER_CENTER,
	CENTER_BOTTOM,
	RIGHT_TOP,
	RIGHT_CENTER,
	RIGHT_BOTTOM,
};

namespace D2D
{
	
	extern ID2D1Factory* pFactory_;
	//extern ID2D1RenderTarget* pRenderTarget_;
	extern IDWriteFontSetBuilder1* pFontSetBuilder_;

	HRESULT Initialize(int winW, int winH, HWND hWnd);
	HRESULT CreateFontCollection();
	IDWriteFontCollection* GetSystemFontCollection();
	ID2D1Factory* Get2DFactory();
	IDWriteFactory5* GetDWriteFactory();
	IDWriteFontCollection1* GetCollection();
	void CreateRenderTarget(const XMINT2 dpiScale, D2D1_RENDER_TARGET_TYPE type= D2D1_RENDER_TARGET_TYPE_DEFAULT,DXGI_FORMAT format= DXGI_FORMAT_UNKNOWN,D2D1_ALPHA_MODE mode= D2D1_ALPHA_MODE_PREMULTIPLIED);
	const int& GetRenderTargetCount();
	ID2D1RenderTarget* GetRenderTarget(int num=0);
	void AllRemoveRenderTarget();
	void Release();
	void RenderTest();
	void BeginDraw();
	void EndDraw();
	int  GetdpiX();
	int  GetdpiY();

};

