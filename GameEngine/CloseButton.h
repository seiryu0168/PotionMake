#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// UI�����{�^��
/// </summary>
class CloseButton : public GameObject
{
public:
	CloseButton(Object* parent);
	~CloseButton();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

