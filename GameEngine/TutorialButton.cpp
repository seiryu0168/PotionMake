#include "TutorialButton.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"Tutorial.h"
#include"CloseButton.h"
TutorialButton::TutorialButton(Object* parent)
	:GameObject(parent,"TutorialButton"),
	isOpenTutorial_(false),
	isSetEnableFunc_(false),
	isSetInvalidFunc_(false)
{
}

void TutorialButton::Initialize()
{
	Image tutorialButton(this);
	tutorialButton.Load("Assets/Image/CloseButtonImage.png");
	tutorialButton.SetSize({ 0.5f,0.5f,0 });
	tutorialButton.SetPosition({ 0.9,0.9,0 });
	AddComponent<Image>(tutorialButton);
}

void TutorialButton::Start()
{
}

void TutorialButton::Update()
{
	if (Input::IsMouseButtonUp(0) && GetComponent<Image>().IsHitCursor()&&!isOpenTutorial_)
	{
		isOpenTutorial_ = true;
		//�`���[�g���A���I�u�W�F�N�g����
		Tutorial* tutorial = Instantiate<Tutorial>(this);
		//�`���[�g���A���Ŏg���摜�Ƃ����Z�b�g
		for (auto& data : tutorialResourceData_)
		{
			tutorial->SetTutorialData(data.first, data.second);
		}
		if(isSetEnableFunc_)
		tutorialEnableFunction_();
		//�`���[�g���A�����鎞�ɌĂяo���֐�
		((CloseButton*)tutorial->FindChild("CloseButton"))->GetFunction() = [&]() {return CloseTutorial(); };

	}
}

void TutorialButton::CloseTutorial()
{
	if(isSetInvalidFunc_)
	tutorialInvalidFunction_();
	isOpenTutorial_ = false;
}

void TutorialButton::SetTutorialData(const std::string& imageName, const std::string& explanation)
{
	tutorialResourceData_.push_back(std::pair<std::string, std::string>(imageName, explanation));
}

void TutorialButton::Release()
{
}
