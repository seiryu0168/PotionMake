#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_MenuUI : public GameObject
{
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
	void Release() override;
};

