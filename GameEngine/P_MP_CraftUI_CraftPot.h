#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// –ò‚ğ’²‡‚·‚é“ç‚ÌƒNƒ‰ƒX
/// </summary>
class P_MP_CraftUI_CraftPot : public GameObject
{
private:
	XMFLOAT2 standPosition_;
	std::vector<XMFLOAT3> resourceImagePos_;
	std::unordered_map<int, int> dataMap_;
public:
	P_MP_CraftUI_CraftPot(Object* parent);
	~P_MP_CraftUI_CraftPot();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void AddResourceData(int itemNum);
	void DisplayResource(int itemNum);
	void Release() override;
};

