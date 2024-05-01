#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// ポーションの制作アニメーションが終わった後のUI
/// </summary>
class FinishCraftUI : public GameObject
{
	int okButtonImageNum_;
	XMFLOAT3 uiPos_;
	int hAudio_Success_;
public:
	FinishCraftUI(Object* parent);
	~FinishCraftUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void DisplayResult(const XMFLOAT3& color);
	void CreateBase();
	void Release() override;
};

