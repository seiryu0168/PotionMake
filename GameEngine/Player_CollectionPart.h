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
public:
	Player_CollectionPart(Object* parent);
	~Player_CollectionPart();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void AddItem(int itemNum);
	//void CameraControll();
	void Release() override;
};
