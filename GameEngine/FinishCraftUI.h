#pragma once
#include"Engine/GameObject/GameObject.h"
class FinishCraftUI : public GameObject
{
public:
	FinishCraftUI(Object* parent);
	~FinishCraftUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

