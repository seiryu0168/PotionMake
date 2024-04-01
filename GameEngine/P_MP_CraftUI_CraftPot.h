#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// –ò‚ğ’²‡‚·‚é“ç‚ÌƒNƒ‰ƒX
/// </summary>
class P_MP_CraftUI_CraftPot : public GameObject
{
private:
	struct ResourceData
	{
		std::string resourceName_;
		std::string imageName_;
		int resourceCount_;
	};
	XMFLOAT2 standPosition_;
	std::vector<GameObject*> objects_;
	std::vector<XMFLOAT3> resourceImagePos_;
	std::unordered_map<int, ResourceData> dataMap_;
public:
	P_MP_CraftUI_CraftPot(Object* parent);
	~P_MP_CraftUI_CraftPot();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void AddResourceData(int itemNum,std::string resourceName,std::string imageName);
	bool SubResourceData(int itemNum);
	void DisplayResource(int itemNum);
	void HiddenResource(int itemNum);
	void Release() override;
};

