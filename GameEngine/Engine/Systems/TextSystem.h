#pragma once
#include"../ECS/System.h"
#include"../Components/Text.h"
class TextSystem : public System
{
public:
	TextSystem();
	~TextSystem() {};
	void Draw(int layerNum) override;
	void CheckRemove() override;
	void Release() override;
};

