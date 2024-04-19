#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_CollectionPart_BaseUI : public GameObject
{
	std::vector<std::string> itemName_;
public:
	Play_CollectionPart_BaseUI(Object* parent);
	~Play_CollectionPart_BaseUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void DisplayItemName(int itemNum);
	void HiddenItemName();
	void Release() override;
};

