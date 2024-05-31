#pragma once
#include"Engine/GameObject/GameObject.h"
class TutorialButton : public GameObject
{
	bool isOpenTutorial_;
	std::vector<std::pair<std::string,std::string>> tutorialResourceData_;
public:
	TutorialButton(Object* parent);
	~TutorialButton() {};

	void Initialize() override;
	void Start() override;
	void Update() override;
	bool IsOpenTutorial() { return isOpenTutorial_; }
	void CloseTutorial();
	void SetTutorialData(const std::string& imageName, const std::string& explanation);
	void Release() override;
};

