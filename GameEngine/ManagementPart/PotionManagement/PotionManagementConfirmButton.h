#pragma once
#include "../../Engine/GameObject/GameObject.h"

//�Ǘ������̃{�^��
class PotionManagementConfirmButton : public GameObject
{
	int hAudio_Confirm_;
public:
	PotionManagementConfirmButton(Object* parent);
	~PotionManagementConfirmButton();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

