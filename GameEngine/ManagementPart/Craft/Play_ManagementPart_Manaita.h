#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// まな板のオブジェクト
/// </summary>
class Play_ManagementPart_Manaita : public GameObject
{
public:
	Play_ManagementPart_Manaita(Object* parent);
	~Play_ManagementPart_Manaita() {};

	void Initialize() override;
	//void Start() override;
	//void Update() override;
	void Release() override;
};

