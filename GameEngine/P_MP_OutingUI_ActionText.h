#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// Ç«Ç±Ç…èoÇ©ÇØÇÈÇ©Çï\é¶Ç∑ÇÈUI
/// </summary>
class P_MP_OutingUI_ActionText : public GameObject
{
public:
	P_MP_OutingUI_ActionText(Object* parent);
	~P_MP_OutingUI_ActionText();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

