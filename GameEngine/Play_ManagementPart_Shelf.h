#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_ManagementPart_Shelf : public GameObject
{
private:
public:
	Play_ManagementPart_Shelf(Object* parent);
	~Play_ManagementPart_Shelf();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

