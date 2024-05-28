#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// すり鉢のオブジェクト
/// </summary>
class Play_ManagementPart_Mortar : public GameObject
{
public:
	Play_ManagementPart_Mortar(Object* parent);
	~Play_ManagementPart_Mortar() {};

	void Initialize() override;
	//void Start() override;
	void Update() override;
	void Release() override;

};

