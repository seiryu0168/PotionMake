#pragma once
#include "../../Engine/GameObject/GameObject.h"
struct ProcessData
{
	int procssNum_;
	float status00_;
	float status01_;
	float status02_;
	float status03_;
	float status04_;
};

/// <summary>
/// ñÚÇí≤çáÇ∑ÇÈìÁÇÃÉNÉâÉX
/// </summary>
class P_MP_CraftUI_CraftPot : public GameObject
{
private:
	struct ResourceData
	{
		std::string resourceName_;
		std::string imageName_;
		int resourceCount_;
		ResourceData()
		{
			resourceName_  = "";
			imageName_     = "";
			resourceCount_ = 0;
		}
		ResourceData(const std::string& resourceName, const std::string& imageName, int resourceCount)
		{
			resourceName_  = resourceName;
			imageName_     = imageName;
			resourceCount_ = resourceCount;
		}
	};
	int cost_;
	int costLimit_;
	int hAudio_Add_;
	int hAudio_Sub_;
	XMFLOAT2 standPosition_;
	std::vector<GameObject*> objects_;
	std::vector<XMFLOAT3> resourceImagePos_;
	std::unordered_map<int, ResourceData> dataMap_;
	std::list<ProcessData> processList_;
	GameObject* potionStatusObject_;
	std::vector<XMFLOAT3> potionColorArray_;
public:

	P_MP_CraftUI_CraftPot(Object* parent);
	~P_MP_CraftUI_CraftPot();
	void Initialize() override;
	void Start() override;
	void Update() override;
	bool AddResourceData(int itemNum,std::string resourceName,std::string imageName);
	bool SubResourceData(int itemNum);
	bool AddProcessData(int processNum);
	bool SubProcessData(int processNum);
	void DisplayResource(int itemNum);
	void HiddenResource(int itemNum);
	void CreatePotion();
	std::vector<float> CalcPotionStatus();
	void Release() override;
};

