#pragma once
#include"Engine/GameObject/GameObject.h"
#include<Functional>
class TutorialButton : public GameObject
{
	std::function<void()> tutorialEnableFunction_;
	std::function<void()> tutorialInvalidFunction_;
	bool isSetEnableFunc_;
	bool isSetInvalidFunc_;
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
	std::function<void()>& GetEnableFunction() { isSetEnableFunc_ = true; return tutorialEnableFunction_; }
	std::function<void()>& GetInvalidFunction() { isSetInvalidFunc_ = true; return tutorialInvalidFunction_; }
	void Release() override;
};

