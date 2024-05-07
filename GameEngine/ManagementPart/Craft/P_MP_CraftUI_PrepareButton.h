#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// 調合開始のボタン
/// </summary>
class P_MP_CraftUI_PrepareButton : public GameObject
{
public:
	P_MP_CraftUI_PrepareButton(Object* parent);
	~P_MP_CraftUI_PrepareButton();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

