#pragma once
#include "../../Window_Base.h"
/// <summary>
/// ��̒����̃x�[�X�ɂȂ�UI
/// ��̕\���Ƃ����H���@�̑I��UI�Ƃ��̓y��
/// </summary>
class P_MP_CraftUI_PrepareUI : public Window_Base
{
public:
	P_MP_CraftUI_PrepareUI(Object* parent);
	~P_MP_CraftUI_PrepareUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

