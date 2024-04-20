#pragma once
#include"Engine/GameObject/GameObject.h"
class P_CP_CollectionedItemUI : public GameObject
{
	XMFLOAT3 uiPos_;
public:
	P_CP_CollectionedItemUI(Object* parent);
	~P_CP_CollectionedItemUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateBase();
	void Release() override;
};

