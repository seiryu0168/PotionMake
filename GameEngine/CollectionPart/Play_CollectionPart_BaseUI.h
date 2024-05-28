#pragma once
#include "../Engine/GameObject/GameObject.h"

class Player_CollectionPart;
/// <summary>
/// 採集パートのベースUI 
/// </summary>
class Play_CollectionPart_BaseUI : public GameObject
{
	std::vector<std::string> itemName_;
	Player_CollectionPart* player_;
	bool isUIOpened_;
	int hAudio_UIOpen_;
public:
	Play_CollectionPart_BaseUI(Object* parent);
	~Play_CollectionPart_BaseUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	//アイテム名を表示
	void DisplayItemName(int itemNum);
	std::vector<std::string>& GetitemNameList() { return itemName_; }
	//アイテム名を非表示
	void HiddenItemName();
	void SetUIOpenFlag(bool flag);
	void Release() override;
};

