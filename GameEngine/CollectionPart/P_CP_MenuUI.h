#pragma once
#include"../UIBase.h"

//採集パートのメニューUI
class P_CP_MenuUI : public UIBase
{
	bool isReturnHome_;
	int returnImageNum_;
	int fadeImageNum_;
	int hAudio_Select_;
	float time_;
public:
	P_CP_MenuUI(Object* parent);
	~P_CP_MenuUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	//入手したアイテムのデータを保存
	void SaveItemData();
	//家に帰る
	void ReturnHome();
	void Release() override;
};

