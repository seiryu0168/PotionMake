#pragma once
#include "../../Engine/GameObject/GameObject.h"
/// <summary>
/// どこに出かけるかを表示するUI
/// </summary>
class P_MP_OutingUI_ActionText : public GameObject
{
	
public:
	P_MP_OutingUI_ActionText(Object* parent);
	~P_MP_OutingUI_ActionText();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Outing(int outNum);
	void Release() override;
};

