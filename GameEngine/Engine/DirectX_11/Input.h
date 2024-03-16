#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dInput.h>
#include"Direct3D.h"
#include"XInput.h"
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")
#pragma comment(lib,"Xinput.lib")
#include"../SAFE_DELETE_RELEASE.h"

static const WORD PUSH = 0xfff0;
static const int NO_PUSHING = -1;

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	int GetConnectedControllerCount() noexcept;
	//キーボード
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);

	//マウス
	bool IsMouseButton(int buttonCode);
	bool IsMouseButtonDown(int buttonCode);
	bool IsMouseButtonUp(int buttonCode);

	//コントローラー
	bool IsPadAnyButton(int padID = 0);
	bool IsPadAnyButtonDown(int padID = 0);
	bool IsPadAnyButtonUp(int padID = 0);
	bool IsPadButton(int buttonCode,int padID = 0);
	bool IsPadButtonDown(int buttonCode, int padID = 0);
	bool IsPadButtonUp(int buttonCode, int padID = 0);
	
	/// <summary>いずれかのゲームパッドの指定したボタンが押されたか返す関数</summary>
	/// <param name="buttonCode">検証するボタンのビットマスク</param>
	/// <returns>押されていれば押したゲームパッドの番号,それ以外ならNO_PUSHING</returns>
	int IsAnyPadDown(int buttonCode) noexcept;

	/// <summary>
	/// どのボタンが押されたか返す関数
	/// </summary>
	/// <param name="padID">検証するコントローラのID</param>
	/// <returns>押されたボタンのビットマスク</returns>
	WORD GetPadAnyButton(int padID = 0);
	WORD GetPadAnyDown(int padID = 0);
	WORD GetPadAnyUp(int padID = 0);

	/// <summary>ボタンが一つだけ押されたときにその値を返す関数</summary>
	/// <param name="padID">検証するコントローラのID</param>
	/// <returns>一つのみの場合は押されたボタンのビットマスク、複数または一つもない場合はNULL</returns>
	WORD GetPadOnlyDown(int padID = 0);
	WORD GetPadOnlyUp(int padID = 0);

	float GetLStick_X(int padID = 0);
	float GetLStick_Y(int padID = 0);
	float GetRStick_X(int padID = 0);
	float GetRStick_Y(int padID = 0);



	float GetLTrigger(int padID = 0);
	float GetLTriggerDown(int padID = 0);
	float GetLTriggerUp(int padID = 0);

	float GetRTrigger(int padID = 0);
	float GetRTriggerDown(int padID = 0);
	float GetRTriggerUp(int padID = 0);

	XMVECTOR GetMousePosition();
	XMVECTOR GetMouseMove();
	void SetMousePosition(int x, int y);
	void Release();

}