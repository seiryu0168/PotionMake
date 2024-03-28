#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// 薬の調合のベースになるUI
/// 鍋の表示とか加工方法の選択UIとかの土台
/// </summary>
class P_MP_CraftUI_PrepareUI : public GameObject
{
public:
	P_MP_CraftUI_PrepareUI(Object* parent);
	~P_MP_CraftUI_PrepareUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

