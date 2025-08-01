//インクルード
#include <Windows.h>
#include<stdlib.h>
#include <thread>
#include"DirectX_11/Direct3D.h"
#include"DirectX_11/Direct2D.h"
#include"GameObject/CameraManager.h"
//#include"DirectX_11/Sprite.h"
//#include"GameObject/Transform.h"
//#include"ResourceManager/ImageManager.h"
//#include"ResourceManager/Model.h"
#include"../DebugUI.h"
#include"DirectX_11/Input.h"
#include"GameObject/RootJob.h"
#include"../ImGui/imgui.h"
#include"../ImGui/imgui_impl_dx11.h"
#include"../ImGui/imgui_impl_win32.h"
#include"ResourceManager/AudioManager.h"
#include"newSceneManager.h"
#include "Time.h"
//#include "Brightness.h"
#include "../Division.h"

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

#pragma comment(lib, "winmm.lib")


//定数宣言
const LPCWSTR WIN_CLASS_NAME = L"PotionStudio";
const LPCWSTR WIN_TITLE_NAME = L"PotionStudio";


const int WINDOW_WIDTH = 1920;   //ウィンドウ幅
const int WINDOW_HEIGHT = 1080;	 //ウィンドウ高さ

//int pxelUnit;
//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//RootJob* pRootJob;

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	//ウィンドウクラス(設計)作成
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	
	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ
	//ウィンドウ作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		WIN_TITLE_NAME,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウ表示
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;
	hr = CoInitialize(nullptr);
	if (FAILED(Direct3D::Initialize(winW, winH, hWnd,{ WINDOW_WIDTH ,WINDOW_HEIGHT})))
	{
		MessageBox(NULL, L"Main:: Direct3Dの初期化に失敗しました", L"エラー", MB_OK);
		PostQuitMessage(0);
	}
	if (FAILED(D2D::Initialize(winW, winH, hWnd, { WINDOW_WIDTH ,WINDOW_HEIGHT })))
	{
		MessageBox(NULL, L"Main:: D2Dの初期化に失敗しました", L"エラー", MB_OK);
		PostQuitMessage(0);
	}


	DebugUI::Initialize(hWnd, Direct3D::GetDevice(), Direct3D::GetContext());
	Input::Initialize(hWnd);
	//ModelManager::Initialize();
	CameraManager::Initialize(winW, winH);
	hr = AudioManager::Initialize();
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Main:: オーディオマネージャーの初期化に失敗しました", L"エラー", MB_OK);
		PostQuitMessage(0);
	}
	Coordinator::Init();

	//Brightness::Initialize();
	Time::Initialize();
	int countFPS = 0;
	//pRootJob = new RootJob;
	
	newSceneManager::Initialize();

	//Division::Initialize();

	//メッセージループ
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			//FPS制限
			//static DWORD countFps = 0;					 //画面更新回数
			//static DWORD startTime = timeGetTime();		 //起動時刻取得(ミリ秒)							//ミリ秒＝10^-3
			DWORD nowTime = timeGetTime();				 //今の時刻取得(ミリ秒)							//1000ミリ秒＝1秒
			static DWORD lastUpdateTime = nowTime;		 //最後に更新した時刻(ミリ秒) : Update
			static DWORD lastFPSResetTime = nowTime;  //最後にFPSを表示した時刻(ミリ秒) : FixedUpdate
			static DWORD lastFixedUpdateTime = nowTime;  //最後に更新した時刻(ミリ秒) : FixedUpdate

			//今の時刻と起動時刻の差が1000ミリ秒超えたら
			//countFpsとstartTimeをリセット
			if (nowTime - lastFPSResetTime >= 1000)
			{
				/*WCHAR str[16];
				wsprintf(str, L"%u", countFps);
				SetWindowText(hWnd, str);*/
				DebugUI::SetFPS(countFPS);
				countFPS = 0;
				lastFPSResetTime = nowTime;//
			}
			//今の時刻と最後に更新した時刻の差*60が1000以上であれば
			if ((nowTime - lastUpdateTime) * 60.0f >= 1000.0f)
			{
				lastUpdateTime = nowTime;
				//std::thread main(Division::threadMain);
				//std::thread load(Division::threadDraw);
				//main.join();
				//load.join();
#ifdef _DEBUG
				DebugUI::StartImGui();
#endif
				//ゲームの処理
				Time::Update();
				Input::Update();

				lastUpdateTime = nowTime;
				//countFps++;
				countFPS++;
				newSceneManager::Update();
				//pRootJob->UpdateSub();
				CameraManager::Update();
#ifdef _DEBUG
				DebugUI::Debug(/*(GameObject*)pRootJob->FindChild("SceneManager")*/);
				//DebugUI::Log();
				ImGui::Render();
#endif 
				newSceneManager::CheckRemoveObject();
				//描画処理
				Direct3D::BeginDraw();

				//pRootJob->ComponentUpdate();
				//D2D::BeginDraw();
				//Coordinator::SystemsUpdate();
				//pRootJob->DrawSub();
				//ビューポート１

				CameraManager::Update();
				//CameraManager::DrawSkdyBox();
				for (int i = 0; i < CameraManager::GetCameraCount(); i++)
				{
					CameraManager::DrawSkdyBox(XMLoadFloat3(&CameraManager::GetCamera(i).GetPosition()));
					//CameraManager::UpdateCameraNum(i);
					//Direct3D::SetViewPort(CameraManager::GetCamera(i).GetViewPort());
				}
					newSceneManager::Draw();
				////ビューポート２
				//{
				//	Direct3D::SetViewPort(1);
				//	//CameraManager::SetPosition(XMVectorSet(10, 10, -10, 0));
				//	//CameraManager::SetTarget(XMVectorSet(0, 0, 0, 0));
				//	CameraManager::Update();
				//	newSceneManager::Draw();
				//}
				//pRootJob->DrawSub();

				//D2D::EndDraw();
				//ImageManager::DrawUI();
				//pRootJob->ThirdDrawSub();
#ifdef _DEBUG	
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
				Direct3D::EndDraw();
			}
		}
	}

	Time::Release();
	//Brightness::Release();
	//AudioManager::Release();
	DebugUI::CleanUp();
	newSceneManager::Release();
	//ImageManager::AllRelease();
	//pRootJob->ReleaseSub();
	//SAFE_DELETE(pRootJob);
	Input::Release();
	D2D::Release();
	Direct3D::Release();

	CoUninitialize();
	return 0;
}
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//ウィンドウプロシージャ(なんかあったら呼ばれる関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd,msg,wParam,lParam))
	{
		return true;
	}

	switch (msg)
	{
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_ACTIVATE:
		BOOL isSuccess_WmActive;
		if (wParam == WA_INACTIVE)
		{
			do
			{}while (ShowCursor(true) < 0);
			ClipCursor(NULL);
		} 
		else if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
		{
			isSuccess_WmActive = ClipCursor(&Direct3D::GetClipRect());
			ShowCursor(Direct3D::GetShowMouseCursor());
		}
		return 0;

	case WM_DESTROY:
		ClipCursor(NULL);
		do
		{} while (ShowCursor(true) < 0);
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

