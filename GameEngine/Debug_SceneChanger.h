#pragma once
#include"Engine/GameObject/Object.h"
class Debug_SceneChanger : Object
{
public:
	Debug_SceneChanger();
	~Debug_SceneChanger();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

