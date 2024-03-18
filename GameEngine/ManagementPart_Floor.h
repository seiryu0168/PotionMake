#pragma once
#include"Engine/GameObject/GameObject.h"
class ManagementPart_Floor : public GameObject
{
private:
	float rotate_;
public:
	ManagementPart_Floor(Object* parent);
	~ManagementPart_Floor();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

