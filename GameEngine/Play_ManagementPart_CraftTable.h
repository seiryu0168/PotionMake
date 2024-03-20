#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_ManagementPart_CraftTable : public GameObject
{
private:
public:
	Play_ManagementPart_CraftTable(Object* parent);
	~Play_ManagementPart_CraftTable();
	void Initialize() override;
	void Update() override;
	void Release() override;

};

