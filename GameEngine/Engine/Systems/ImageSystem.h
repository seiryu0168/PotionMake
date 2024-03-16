#pragma once
#include"../ECS/System.h"
#include"../Components/Image.h"
class ImageSystem : public System
{
public:
	ImageSystem();
	~ImageSystem() {};
	void Draw(int layerNum) override;
	void CheckRemove() override;
	void Release() override;
	int IsHitCursorAny();
};