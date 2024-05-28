#pragma once
#include "../Engine/GameObject/GameObject.h"
/// <summary>
/// 地面のオブジェクト
/// </summary>
class CollectionPart_Ground : public GameObject
{
public:
	CollectionPart_Ground(Object* parent);
	~CollectionPart_Ground();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

