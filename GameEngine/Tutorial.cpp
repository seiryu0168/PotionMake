#include "Tutorial.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"CloseButton.h"
namespace
{
	XMFLOAT3 StayPosition = { 0,2,0 };
	XMFLOAT3 DisplayPosition = { 0,0.3f,0 };
}
Tutorial::Tutorial(Object* parent)
	:GameObject(parent,"Tutorial"),
	currentTutorialIndex_(-1),
	prevTutorialIndex_(-1)
{
}

void Tutorial::Initialize()
{
	CloseButton* btn = Instantiate<CloseButton>(this);
	btn->GetComponent<Image>().SetPosition({ -0.8,0.9,0 });

	Text explanationText(this);
	explanationText.SetRect({ 0,0,1000,500 });
	explanationText.SetRatio(0.24f, 0.6f);
	explanationText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	explanationText.SetText("");
	AddComponent<Text>(explanationText);

	time_ = std::make_shared<Time::Watch>();
	time_->UnLock();
	//explanationText.SetFont("‚è‚¢‚Ä‚ª‚«")
}

void Tutorial::Start()
{
	if (tutorialDataList_.size() > 0)
		currentTutorialIndex_ = 0;
	GetComponent<Image>(tutorialDataList_[currentTutorialIndex_].first).SetPosition(DisplayPosition);
	GetComponent<Text>().SetText(tutorialDataList_[currentTutorialIndex_].second);
}

void Tutorial::Update()
{
	if (tutorialDataList_.size()>0 && Input::IsMouseButtonUp(0)&&time_->GetSeconds<float>() >= 0.5f)
	{

		prevTutorialIndex_ = currentTutorialIndex_;
		if (currentTutorialIndex_ < tutorialDataList_.size()-1)
			currentTutorialIndex_++;
		GetComponent<Image>(tutorialDataList_[prevTutorialIndex_].first).SetPosition(StayPosition);
		GetComponent<Image>(tutorialDataList_[currentTutorialIndex_].first).SetPosition(DisplayPosition);
		GetComponent<Text>().SetText(tutorialDataList_[currentTutorialIndex_].second);
		time_->SetSecond(0);
	}
}

void Tutorial::SetTutorialData(const std::string& imageName, const std::string& explanation)
{
	Image tutorial(this);
	tutorial.Load(imageName);
	tutorial.SetPosition(StayPosition);
	//AddComponent<Image>(tutorial);
	std::pair<int, std::string> tutorialData;
	tutorialData.first= AddComponent<Image>(tutorial);
	tutorialData.second = explanation;
	tutorialDataList_.push_back(tutorialData);
}

void Tutorial::Release()
{
}
