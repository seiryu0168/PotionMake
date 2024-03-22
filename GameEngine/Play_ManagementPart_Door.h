#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_ManagementPart_Door : public GameObject
{
private:
public:
	Play_ManagementPart_Door(Object* parent);
	~Play_ManagementPart_Door();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

