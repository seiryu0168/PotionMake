#pragma once
#include"../Engine/GameObject/GameObject.h"
class SnowCone_Topping : public GameObject
{
private:
public:
	SnowCone_Topping(Object* parent);
	~SnowCone_Topping();

	void Initialize() override;
	void Release() override;
};

