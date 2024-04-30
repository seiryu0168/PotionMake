#pragma once
//#include"Engine/GameObject/GameObject.h"
#include"Player.h"
class Play_ManagementPart_BaseUI;
class P_CP_Player_ItemGetter;
class CollectionPart_Ground;
class Play_UIManager;

class Player_CollectionPart : public Player
{
private:
	P_CP_Player_ItemGetter* itemGetter_;
	CollectionPart_Ground* ground_;
	Play_UIManager* uiManager_;
	std::unordered_map<int, int> itemCount_;
	bool canControl_;
public:
	Player_CollectionPart(Object* parent);
	~Player_CollectionPart();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void MoveControll() override;
	void AddItem(int itemNum);
	void SetControllFlag(bool flag) { canControl_ = flag; }
	const std::unordered_map<int, int>& GetItem() { return itemCount_; }
	//void CameraControll();
	void Release() override;
};

