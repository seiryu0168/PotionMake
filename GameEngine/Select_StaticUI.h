#pragma once
#include"Engine/GameObject/GameObject.h"

class Image;

class Select_StaticUI : public GameObject
{
private:
	int Frame_;
	std::vector<Image*> backGroundImageList_;
	int hAudio_;
public:
	Select_StaticUI(Object* parent);
	~Select_StaticUI();

	void Initialize() override;
	void Update() override;
	void Release() override;
};

