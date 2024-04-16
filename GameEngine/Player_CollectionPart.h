#pragma once
//#include"Engine/GameObject/GameObject.h"
#include"Player.h"
class Play_ManagementPart_BaseUI;

class Player_CollectionPart : public Player
{
private:

public:
	Player_CollectionPart(Object* parent);
	~Player_CollectionPart();
	void Initialize() override;
	void Start() override;
	void Update() override;
	//void CameraControll();
	void Release() override;
};

