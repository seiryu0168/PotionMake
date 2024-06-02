#pragma once
#include"Engine/GameObject/GameObject.h"
#include"Engine/Time.h"
class Tutorial : public GameObject
{
	std::shared_ptr<Time::Watch> time_;
	int currentTutorialIndex_;
	int prevTutorialIndex_;
	int maxIndex_;
	int currentPageImageNum_;
	std::vector<XMFLOAT3> dotPos_;
	std::vector<std::pair<int, std::string>> tutorialDataList_;
public:
	Tutorial(Object* parent);
	~Tutorial() {};

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetTutorialData(const std::string& imageName, const std::string& explanation);
	void CreatePageCount();
	void Release() override;
};

