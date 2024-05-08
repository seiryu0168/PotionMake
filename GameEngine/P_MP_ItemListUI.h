#pragma once
#include"Engine/GameObject/GameObject.h"
class P_MP_ItemListUI : public GameObject
{
	XMFLOAT3 uiPos_;
	std::vector<int> itemNumList_;
public:
	P_MP_ItemListUI(Object* parent);
	~P_MP_ItemListUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateBase();
	void SetSelectFlag(bool flag);
	void Release() override;
};

