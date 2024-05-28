#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// 採集パートのアイテムを設置するクラス
/// </summary>
class Play_CollectionPart_StageManager : public GameObject
{
private:
	//std::vector<std::string> itemNameLIst_;
public:
	Play_CollectionPart_StageManager(Object* parent);
	~Play_CollectionPart_StageManager();

	void Initialize() override;
	void Update() override;
	std::vector<std::string> GetItemNameList();
	std::string ConvertItemName(const std::string& str);
	void Release() override;
};

