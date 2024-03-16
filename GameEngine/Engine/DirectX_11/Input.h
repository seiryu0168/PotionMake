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
	//�L�[�{�[�h
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);

	//�}�E�X
	bool IsMouseButton(int buttonCode);
	bool IsMouseButtonDown(int buttonCode);
	bool IsMouseButtonUp(int buttonCode);

	//�R���g���[���[
	bool IsPadAnyButton(int padID = 0);
	bool IsPadAnyButtonDown(int padID = 0);
	bool IsPadAnyButtonUp(int padID = 0);
	bool IsPadButton(int buttonCode,int padID = 0);
	bool IsPadButtonDown(int buttonCode, int padID = 0);
	bool IsPadButtonUp(int buttonCode, int padID = 0);
	
	/// <summary>�����ꂩ�̃Q�[���p�b�h�̎w�肵���{�^���������ꂽ���Ԃ��֐�</summary>
	/// <param name="buttonCode">���؂���{�^���̃r�b�g�}�X�N</param>
	/// <returns>������Ă���Ή������Q�[���p�b�h�̔ԍ�,����ȊO�Ȃ�NO_PUSHING</returns>
	int IsAnyPadDown(int buttonCode) noexcept;

	/// <summary>
	/// �ǂ̃{�^���������ꂽ���Ԃ��֐�
	/// </summary>
	/// <param name="padID">���؂���R���g���[����ID</param>
	/// <returns>�����ꂽ�{�^���̃r�b�g�}�X�N</returns>
	WORD GetPadAnyButton(int padID = 0);
	WORD GetPadAnyDown(int padID = 0);
	WORD GetPadAnyUp(int padID = 0);

	/// <summary>�{�^��������������ꂽ�Ƃ��ɂ��̒l��Ԃ��֐�</summary>
	/// <param name="padID">���؂���R���g���[����ID</param>
	/// <returns>��݂̂̏ꍇ�͉����ꂽ�{�^���̃r�b�g�}�X�N�A�����܂��͈���Ȃ��ꍇ��NULL</returns>
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