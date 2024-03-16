#pragma once
#include"../Engine/GameObject/GameObject.h"

class SnowCone_Table : public GameObject
{
private:

public:
	SnowCone_Table(Object* parent);
	~SnowCone_Table();
	void Initialize() override;
	void Release() override;
};

