#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// 入手したアイテムの詳細を表示するクラス
/// </summary>
class PickupedItemDetailUI : public GameObject
{
	XMFLOAT3 uiPos_;
	int hAudio_OpenUI_;
public:
	PickupedItemDetailUI(Object* parent);
	~PickupedItemDetailUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItemData(int itemNum);
	void Release() override;
};

