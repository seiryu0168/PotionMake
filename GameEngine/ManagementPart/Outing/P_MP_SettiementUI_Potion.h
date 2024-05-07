#pragma once
#include "../../Engine/GameObject/GameObject.h"
class P_MP_SettiementUI_Potion : public GameObject
{
	int potionTier_;
	std::string potionName_;
	XMFLOAT3 potionColor_;
	XMFLOAT3 firstPos_;

	bool isSetFirstPosition_;
	int price_;
	int totalGain_;

	float time_;
public:
	P_MP_SettiementUI_Potion(Object* parent);
	~P_MP_SettiementUI_Potion();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetPotionData(int potionTier, const std::string& name, const XMFLOAT3& color, int price);
	void SetFirstPosition(const XMFLOAT3& pos);
	void AddPosition(float move);
	void Release() override;
};

