#pragma once
#include "../Engine/GameObject/GameObject.h"

class Player_CollectionPart;
/// <summary>
/// �̏W�p�[�g�̃x�[�XUI 
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
	//�A�C�e������\��
	void DisplayItemName(int itemNum);
	std::vector<std::string>& GetitemNameList() { return itemName_; }
	//�A�C�e�������\��
	void HiddenItemName();
	void SetUIOpenFlag(bool flag);
	void Release() override;
};

