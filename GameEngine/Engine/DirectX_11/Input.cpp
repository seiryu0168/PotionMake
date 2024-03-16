#include "Input.h"

namespace
{
	constexpr float TILT_MAX	= 32768.0f;
	constexpr float TRIGGER_MAX = 255.0f;
	const int		PAD_MAX		= 4;
	//�Q�[���p�b�h�̊e�{�^���̔z��
	/*const WORD Code[] = { XINPUT_GAMEPAD_DPAD_UP, XINPUT_GAMEPAD_DPAD_DOWN, XINPUT_GAMEPAD_DPAD_LEFT, XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_START, XINPUT_GAMEPAD_BACK, XINPUT_GAMEPAD_LEFT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB,
		XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER,
		XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y };*/
}

namespace Input
{

		LPDIRECTINPUT8   pDInput = nullptr;				//�|�C���^�Ȃ̂ł��ƂŃ����[�X
		LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;		//�L�[�f�o�C�X
		LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;	//�}�E�X�f�o�C�X
		XINPUT_STATE Controller_[PAD_MAX];				//�R���g���[���[�̏��
		XINPUT_STATE prevController_[ PAD_MAX ];		//�O�t���[���̃R���g���[���[�̏��
		BYTE keyState[256] = { 0 };						//������Ă邩�ǂ������肷��ϐ�
		BYTE prevKeyState[256] = { 0 };					//�O�t���[��������Ă����ǂ���
		XMVECTOR mousePosition;

		DIMOUSESTATE mouseState;
		DIMOUSESTATE prevMouseState;

		int connectedController_;

	void Initialize(HWND hWnd)
	{
		//�Ƃ肠���������Ƃ�
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);

		//�L�[�{�[�h
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);					//�f�o�C�X�I�u�W�F�N�g�쐬
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);										//�f�o�C�X�̎�ގw��
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);	//�������x���ݒ�

		//�}�E�X
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//�R���g���[���[
		for (int i = 0; i < PAD_MAX; i++)
		{

			ZeroMemory(&Controller_[i], sizeof(XINPUT_STATE));
			ZeroMemory(&prevController_[i], sizeof(XINPUT_STATE));
		}
	}

	void Update()
	{
		memcpy(&prevKeyState, &keyState, sizeof(keyState));				//�O�t���[���̏�Ԃ��R�s�[
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);		//�L�[���ׂ�

		pMouseDevice->Acquire();
		memcpy(&prevMouseState, &mouseState, sizeof(mouseState));		//�O�t���[���̏�Ԃ��R�s�[
		pMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);	//�}�E�X���ׂ�

		DWORD result;
		int connected = 0;
		for (int i = 0; i < PAD_MAX; i++)
		{
			memcpy(&prevController_[i], &Controller_[i], sizeof(Controller_[i]));
			result = XInputGetState(i, &Controller_[i]);
			if (result == ERROR_SUCCESS)
				++connected;

		}
		connectedController_ = connected;

	}
	int GetConnectedControllerCount() noexcept
	{
		return connectedController_;
	}
	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsKeyDown(int keyCode)
	{
		if ((keyState[keyCode] & 0x80) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsKeyUp(int keyCode)
	{
		if (!(keyState[keyCode] & 0x80) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButton(int buttonCode)
	{
		if (mouseState.rgbButtons[buttonCode]  & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonDown(int buttonCode)
	{
		if ((mouseState.rgbButtons[buttonCode]  & 0x80)&&!(prevMouseState.rgbButtons[buttonCode]  & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonUp(int buttonCode)
	{
		if (!(mouseState.rgbButtons[buttonCode] & 0x80) && (prevMouseState.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsPadAnyButton(int padID)
	{
		return Controller_[padID].Gamepad.wButtons != 0;
	}
	bool IsPadAnyButtonDown(int padID)
	{
		if (IsPadAnyButton(padID) && prevController_[padID].Gamepad.wButtons != 0)
			return true;
		return false;
	}
	bool IsPadAnyButtonUp(int padID)
	{
		if (!IsPadAnyButton(padID) && prevController_[padID].Gamepad.wButtons != 0)
			return true;
		return false;
	}
	bool IsPadButton(int buttonCode, int padID)
	{
		return (Controller_[padID].Gamepad.wButtons & buttonCode) != 0;
	}
	
	bool IsPadButtonDown(int buttonCode, int padID)
	{
		if (IsPadButton(buttonCode,padID)&&!(prevController_[padID].Gamepad.wButtons & buttonCode))
		{
			return true;
		}
		return false;
	}
	bool IsPadButtonUp(int buttonCode, int padID)
	{
		if (!IsPadButton(buttonCode, padID) && (prevController_[padID].Gamepad.wButtons & buttonCode))
		{
			return true;
		}
		return false;
	}

	int IsAnyPadDown(int buttonCode) noexcept
	{
		for (int i = 0; i < PAD_MAX; i++)
		{
			if (IsPadButtonDown(buttonCode, i))
				return i;
		}
		return NO_PUSHING;
	}

	WORD GetPadAnyButton(int padID)
	{
		return Controller_[padID].Gamepad.wButtons;
	}

	WORD GetPadAnyDown(int padID)
	{
		//���݂ƒ��O�̏�Ԃ̔r���I�_���a���擾���A���݉����ꂽ�r�b�g�݂̂�_���ςŎc��
		return (Controller_[padID].Gamepad.wButtons ^ prevController_[padID].Gamepad.wButtons) & Controller_[padID].Gamepad.wButtons;

		/*if (Controller_[padID].Gamepad.wButtons != 0 && prevController_[padID].Gamepad.wButtons == 0)
			return prevController_[padID].Gamepad.wButtons;
		else
			return NULL;*/
			//return 0;
		//return Controller_[padID].Gamepad.wButtons & 0xffff;

		//for (WORD i : Code)
		//{
		//	if (IsPadButtonDown(i, padID))
		//		return i;
		//}
		//
		//return NO_PUSH;
	}

	WORD GetPadAnyUp(int padID)
	{
		return (Controller_[padID].Gamepad.wButtons ^ prevController_[padID].Gamepad.wButtons) & prevController_[padID].Gamepad.wButtons;

		/*if (Controller_[padID].Gamepad.wButtons == 0 && prevController_[padID].Gamepad.wButtons != 0)
			return Controller_[padID].Gamepad.wButtons;
		else
			return PUSH;
		return WORD();*/
	}

	WORD GetPadOnlyDown(int padID)
	{
		WORD ans = GetPadAnyDown(padID);

		if (std::has_single_bit(ans))
		{
			return ans;
		}
		return NULL;
	}

	WORD GetPadOnlyUp(int padID)
	{
		WORD ans = GetPadAnyUp(padID);

		if (std::has_single_bit(ans))
		{
			return ans;
		}
		return NULL;
	}

	float GetLStick_X(int padID)
	{
		INT tilt = Controller_[padID].Gamepad.sThumbLX;
		if (fabs(tilt) >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			return (powf(tilt, 2) - (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * fabs(tilt))) / (tilt * TILT_MAX);
			/*(fabs(tilt)/tilt)*((fabs(tilt)- XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)*/
		}
		return 0;
	}
	float GetLStick_Y(int padID)
	{
		INT tilt = Controller_[padID].Gamepad.sThumbLY;
		if (fabs(tilt) >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			return (powf(tilt, 2) - (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * fabs(tilt))) / (tilt * TILT_MAX);
				/*(fabs(tilt)/tilt)*((fabs(tilt)- XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)*/
		}
		return 0;
	}
	float GetRStick_X(int padID)
	{
		INT tilt = Controller_[padID].Gamepad.sThumbRY;
		if (fabs(tilt) >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			return (powf(tilt, 2) - (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE * fabs(tilt))) / (tilt * TILT_MAX);
			/*(fabs(tilt)/tilt)*((fabs(tilt)- XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)*/
		}
		return 0;
	}
	float GetRStick_Y(int padID)
	{
		INT tilt = Controller_[padID].Gamepad.sThumbRY;
		if (fabs(tilt) >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			return (powf(tilt, 2) - (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE * fabs(tilt))) / (tilt * TILT_MAX);
			/*(fabs(tilt)/tilt)*((fabs(tilt)- XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)*/
		}
		return 0;
	}

	float GetLTrigger(int padID)
	{
		if (Controller_[padID].Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			return (Controller_[padID].Gamepad.bLeftTrigger- XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / TRIGGER_MAX;
		}
		return 0;
	}
	float GetLTriggerDown(int padID)
	{
		if (Controller_[padID].Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && prevController_[padID].Gamepad.bLeftTrigger< XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			return (Controller_[padID].Gamepad.bLeftTrigger- XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / TRIGGER_MAX;
		}
		return 0;
	}
	float GetLTriggerUp(int padID)
	{
		if (Controller_[padID].Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD && prevController_[padID].Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			return (Controller_[padID].Gamepad.bLeftTrigger- XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / TRIGGER_MAX;
		}
		return 0;
	}


	float GetRTrigger(int padID)
	{
		if (Controller_[padID].Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			return (Controller_[padID].Gamepad.bRightTrigger- XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / TRIGGER_MAX;
		}
		return 0;
	}
	float GetRTriggerDown(int padID)
	{
		if (Controller_[padID].Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && prevController_[padID].Gamepad.bRightTrigger< XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			return (Controller_[padID].Gamepad.bRightTrigger- XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / TRIGGER_MAX;
		}
		return 0;
	}
	float GetRTriggerUp(int padID)
	{
		if (Controller_[padID].Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD && prevController_[padID].Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			return (Controller_[padID].Gamepad.bRightTrigger- XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / TRIGGER_MAX;
		}
		return 0;
	}


	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	XMVECTOR GetMouseMove()
	{
		XMVECTOR move = XMVectorSet((float)mouseState.lX, (float)mouseState.lY, (float)mouseState.lZ,0);
		return move;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
	}
}