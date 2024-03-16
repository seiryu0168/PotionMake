#pragma once
#include"../Engine/GameObject/GameObject.h"
#include<random>
class Shooting_Table : public GameObject
{
private:
	
public:
	Shooting_Table(Object* parent);
	~Shooting_Table();
	void Initialize() override;
	void Release() override;
};

