#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// �\����f�ނƉ��H���@�Ő؂�ւ���{�^��
/// </summary>
class ResourceMenuChangeButton : public GameObject
{
public:
	ResourceMenuChangeButton(Object* parent);
	~ResourceMenuChangeButton();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

