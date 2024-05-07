#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// 情報のないダミーのポーション枠
/// </summary>
class PotionStockDummy : public GameObject
{
public:
	PotionStockDummy(Object* parent);
	~PotionStockDummy();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

