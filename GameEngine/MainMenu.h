#pragma once
#include"Engine/GameObject/GameObject.h"
class MainMenu : public GameObject
{
private:
public:
	MainMenu(Object* parent);
	~MainMenu();
	void Initialize() override;
	void Update() override;
	void Release() override;

};

