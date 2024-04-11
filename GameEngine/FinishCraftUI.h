#pragma once
#include"Engine/GameObject/GameObject.h"
class FinishCraftUI : public GameObject
{
	int okButtonImageNum_;
public:
	FinishCraftUI(Object* parent);
	~FinishCraftUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void DisplayResult(const XMFLOAT3& color);
	void Release() override;
};

