#pragma once
#include"Engine/GameObject/GameObject.h"
class ResourceMenuChangeButton : public GameObject
{
public:
	ResourceMenuChangeButton(Object* parent);
	~ResourceMenuChangeButton();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

