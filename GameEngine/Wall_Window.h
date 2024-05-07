#pragma once
#include "Engine/GameObject/GameObject.h"
class Wall_Window : public GameObject
{
public:
	Wall_Window(Object* parent);
	~Wall_Window();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

