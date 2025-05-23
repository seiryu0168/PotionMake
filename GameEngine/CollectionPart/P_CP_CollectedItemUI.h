#pragma once
#include "../Engine/GameObject/GameObject.h"
/// <summary>
/// 入手したアイテムを表示するクラス
/// </summary>
class P_CP_CollectedItemUI : public GameObject
{
	XMFLOAT3 uiPos_;
	XMFLOAT2 diffPos_;
	int stockCount_;
	std::vector<int> itemNumList_;
public:
	P_CP_CollectedItemUI(Object* parent);
	~P_CP_CollectedItemUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateBase();
	//アイテムの番号、名前等のデータを入れる
	void SetItemData(int itemNum, const std::string& itemName, int itemCount, const std::string& itemImageName);
	//ダミー画像入れる
	void SetDummy();
	const std::vector<int>& GetItemNumList() { return itemNumList_; }
	void SetSelectFlag(bool flag);
	void Release() override;
};

