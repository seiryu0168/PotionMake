#include "Tutorial.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/AudioSystem.h"
#include"CloseButton.h"
namespace
{
	XMFLOAT3 StayPosition = { 0,2,0 };
	XMFLOAT3 DisplayPosition = { 0,0.3f,0 };
	XMFLOAT3 FitstPagePos = { 0.0f,-0.7f,0 };
	float pageDotWidth = 0.5f;
}
Tutorial::Tutorial(Object* parent)
	:GameObject(parent,"Tutorial"),
	currentTutorialIndex_(-1),
	prevTutorialIndex_(-1),
	maxIndex_(0),
	currentPageImageNum_(-1)
{
}

void Tutorial::Initialize()
{

	Image backImage(this);
	backImage.Load("Assets/Image/UIBaseImage3.png");
	backImage.SetSize({ 35.0f,18.0f,0 });
	backImage.SetColor(0.3f);
	backImage.SetLayer(2);
	AddComponent<Image>(backImage);

	Text explanationText(this);
	explanationText.SetRect({ 0,0,1000,500 });
	explanationText.SetLayer(2);
	explanationText.SetTextSize(40);
	explanationText.SetRatio(0.24f, 0.6f);
	explanationText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	explanationText.SetText("");
	AddComponent<Text>(explanationText);

	time_ = std::make_shared<Time::Watch>();
	time_->UnLock();

	Audio audio(this);
	audio.Load("Assets/Audio/Confirm34.wav", false, 1.0f, 3);
	AddComponent<Audio>(audio);

	CloseButton* btn = Instantiate<CloseButton>(this);
	btn->GetComponent<Image>().SetPosition({ -0.8,0.9,0 });
	btn->GetComponent<Image>().SetLayer(2);
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
		//現在のインデックスをprevTutorialIndex_に代入
		prevTutorialIndex_ = currentTutorialIndex_;
		//インデックスが配列のサイズ以下なら
		if (currentTutorialIndex_ < tutorialDataList_.size() - 1)
		{

			currentTutorialIndex_++;
			//音ならす
			GetComponent<Audio>().Play();
			//画像変える
			GetComponent<Image>(tutorialDataList_[prevTutorialIndex_].first).SetPosition(StayPosition);
			GetComponent<Image>(tutorialDataList_[currentTutorialIndex_].first).SetPosition(DisplayPosition);
			GetComponent<Text>().SetText(tutorialDataList_[currentTutorialIndex_].second);

			GetComponent<Image>(currentPageImageNum_).SetPosition(dotPos_[currentTutorialIndex_]);

			time_->SetSecond(0);
		}
	}
}

void Tutorial::SetTutorialData(const std::string& imageName, const std::string& explanation)
{
	Image tutorial(this);
	tutorial.Load("Assets/Image/"+imageName);
	tutorial.SetLayer(2);
	tutorial.SetPosition(StayPosition);
	//AddComponent<Image>(tutorial);
	std::pair<int, std::string> tutorialData;
	tutorialData.first= AddComponent<Image>(tutorial);
	tutorialData.second = explanation;
	tutorialDataList_.push_back(tutorialData);
	maxIndex_++;
}

void Tutorial::CreatePageCount()
{
	float diffX = -pageDotWidth*0.5f;
	//XMFLOAT2 diffPos = { -0.2f,0 };
	for (int i = 0; i < maxIndex_; i++)
	{
		Image image(this);
		image.Load("Assets/Image/PageDot.png");
		image.SetColorInt({ 60,60,60 });
		image.SetLayer(2);
		image.SetPosition({ FitstPagePos.x + diffX,FitstPagePos.y,0 });
		AddComponent<Image>(image);

		dotPos_.push_back({ FitstPagePos.x + diffX,FitstPagePos.y,0 });
		diffX += pageDotWidth / maxIndex_;
	}

	Image currentImage(this);
	currentImage.Load("Assets/Image/PageDot.png");
	currentImage.SetColorInt({ 235,239,138 });
	currentImage.SetLayer(2);
	currentImage.SetPosition(dotPos_[0]);
	currentPageImageNum_ = AddComponent<Image>(currentImage);
}

void Tutorial::Release()
{
}
