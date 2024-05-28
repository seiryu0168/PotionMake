#pragma once
#include"UIBase.h"

/// <summary>
/// 経営パートのメニューUI
/// </summary>
class P_MP_MenuUI : public UIBase
{
	//bool isOpenUI_;
	int returnImageNum_;
	int saveImageNum_;
	int hAudio_Confirm_;
public:
	P_MP_MenuUI(Object* parent);
	~P_MP_MenuUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void DataSave();
	//void SetOpenUIFlag(bool flag) { isOpenUI_ = flag; }
	void Release() override;
};

