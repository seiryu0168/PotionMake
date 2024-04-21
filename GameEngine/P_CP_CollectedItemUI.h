#pragma once
#include"Engine/GameObject/GameObject.h"
class P_CP_CollectedItemUI : public GameObject
{
	XMFLOAT3 uiPos_;
	std::vector<int> itemNumList_;
public:
	P_CP_CollectedItemUI(Object* parent);
	~P_CP_CollectedItemUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateBase();
	const std::vector<int>& GetItemNumList() { return itemNumList_; }
	void SetSelectFlag(bool flag);
	void Release() override;
};

