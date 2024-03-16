#include "SnowConeMaking.h"
#include"../Engine/GameObject/CameraManager.h"
#include"../Engine/DirectX_11/Input.h"
#include"../Engine/Systems/ImageSystem.h"
#include"../Engine/Systems/TextSystem.h"
#include"../Engine/newSceneManager.h"
#include"../InterSceneData.h"

#include"SnowConeMaker_Shave.h"
#include"SnowConeMaker_Topping.h"
#include"SnowCone_Table.h"
#include"SnowCone_Cup.h"
#include"SnowCone_Order.h"

#include<format>

namespace
{
	static const XMFLOAT3 cupPos[3] = { {-10,0,0},{0,0,0},{10,0,0} };
	static const XMFLOAT3 STOCK_POS[3]{ {1220,850,0},{1470,850,0},{1720,850,0} };
	static const XMFLOAT2 STOCK_TEXT_POS[3]{ {1515,200},{1640,200 }, {1765,200} };
	static const XMFLOAT2 COUNT_POS = { 700,50 };
	static const XMFLOAT3 PROGRESS_DEFAULT = { 2,1,0 };
	static const std::string STOCK_TEXT[3] = { "����","����","�吷" };
	static const float PLAY_COUNT = 60.0f;
	static const int STOCK_LIMIT = 3;
}
SnowConeMaking::SnowConeMaking(Object* parent)
	:Framework(parent,"SnowConeMaking"),
	state_(PLAY_STATE::STATE_STAY),
	progressImageNum_(0),
	explanationNum_(0),
	explanationNum2_(0),
	copuntFlag_(0)
{
}

SnowConeMaking::~SnowConeMaking()
{
}

void SnowConeMaking::Initialize()
{
	CameraManager::AllRmoveCamera();
	D2D::AllRemoveRenderTarget();
	//�J�����p��
	//���j���[�Ƃ��\�������Ԃł����J����
	{
		Camera camera;
		XMINT2 WH = { Direct3D::GetScreenWidth() ,Direct3D::GetScreenHeight() };
		camera.Initialize(WH.x, WH.y, 1.0f, 500.0f);
		camera.SetViewPort(WH.x, WH.y, 0.0f, 1.0f, 0, 0);
		CameraManager::AddCamera(camera);

	}
	//�v���C���[1�̃J����
	{
		Camera camera;
		XMINT2 WH = { Direct3D::GetScreenWidth() ,Direct3D::GetScreenHeight() };
		camera.Initialize(WH.x, WH.y, 1.0f, 500.0f);
		camera.SetViewPort(WH.x / 2.0f, WH.y / 2.0f, 0.0f, 1.0f, 0, WH.y / 4.0f);
		CameraManager::AddCamera(camera);
	}
	//�v���C���[2�̃J����
	{
		Camera camera;
		XMINT2 WH = { Direct3D::GetScreenWidth() ,Direct3D::GetScreenHeight() };
		camera.Initialize(WH.x, WH.y, 1.0f, 500.0f);
		camera.SetViewPort(WH.x / 2.0f, WH.y / 2.0f, 0.0f, 1.0f, WH.x/2.0f, WH.y / 4.0f);
		CameraManager::AddCamera(camera);
	}
	//�X�g�b�N�\���p�̉摜�p��
	for (int i = 0; i < 3; i++)
	{
		Image backImage(0, 1);
		backImage.Load("Assets/Image/SnowCone_ShavedImage.png");
		backImage.SetPositionAtPixel(STOCK_POS[i]);
		backImage.SetSize({ 1.4f,1.4f,0 });
		backImage.SetColor({ 0,0,0 });
		backImage.SetAlpha(0.7f);
		AddComponent<Image>(backImage);

		Image image(0, 1);
		image.Load("Assets/Image/SnowCone_ShavedImage.png");
		image.SetPositionAtPixel(STOCK_POS[i]);
		image.SetSize({ 1.3f,1.3f,0 });
		image.SetAlpha(0);
		shavedCupList_.push_back(AddComponent<Image>(image));

		Text shavedText("", "�肢�Ă����M", { 0,0,100,50 });
		shavedText.SetPosition(STOCK_TEXT_POS[i]);
		shavedText.SetTextSize(30);
		shavedText.SetColor({ 0,0,0,1 });
		shavedText.SetAlignmentType(CENTER_CENTER);
		shavedCupSize_.push_back(AddComponent<Text>(shavedText));
	}
	//�v���C���[1,2�̔w�i�p��
	for(int i=0;i<2;i++)
	{
		Image tableImage(i + 1,0);
		tableImage.Load("Assets/Image/plywood_diff_1k.jpg");
		tableImage.SetSize({ 2,2,0 });
		AddComponent<Image>(tableImage);
		Image image(i+1);
		image.Load("Assets/Image/MultiWindowFrame.png");
		AddComponent<Image>(image);
	}
	//�S�̂̔w�i�p��
	Image image(0);
	image.Load("Assets/Image/SnowCone_CommandImage2.png");
	AddComponent<Image>(image);
	//�������ԗp�̉摜
	Image progressImage(0);
	progressImage.Load("Assets/Image/ProgressBar_Image.png");
	progressImage.SetSize(PROGRESS_DEFAULT);
	progressImage.SetPositionAtPixel({ -1920,-800,0 });
	progressImageNum_ = AddComponent<Image>(progressImage);
	
	//�n�܂�O�̃J�E���g�_�E���p�e�L�X�g
	Text countText("", "�肢�Ă����M", { 0,0,500,50 },0,2);
	countText.SetPosition(COUNT_POS);
	countText.SetColor({ 0, 0, 0, 1 });
	countText.SetAlignmentType(CENTER_CENTER);
	countText.SetTextSize(200);
	timeText_ = AddComponent<Text>(countText);

	//�����N���X�ƃe�[�u���N���X��ҋ@�����Ă���
	Instantiate<SnowCone_Order>(this)->SetActive(false);
	Instantiate<SnowCone_Table>(this)->SetActive(false);
	//�����X�����N���X�𐶐�
	SnowConeMaker_Shave* p1 = Instantiate<SnowConeMaker_Shave>(this);
	p1->SetPlayerNumber(0);
	p1->SetUpdate(false);
	//�g�b�s���O��I�ԃN���X�𐶐�
	SnowConeMaker_Topping* p2 = Instantiate<SnowConeMaker_Topping>(this);
	p2->SetPlayerNumber(1);
	p2->SetUpdate(false);
	//���Ԃ�������
	time_ = std::make_unique<Time::Watch>();
	time_->SetCountdown(true);
	
	//�X�R�A�}�l�[�W���[�̏�����
	scoreManager_.Init(1, 0);
	{
		Image image(1, 2);
		image.Load("Assets/Image/SnowCone_PocessImage01.png");
		explanationNum_=AddComponent<Image>(image);
	}
	{
		Image image(2, 2);
		image.Load("Assets/Image/SnowCone_PocessImage02.png");
		explanationNum2_ = AddComponent<Image>(image);
	}
}

void SnowConeMaking::Update()
{
	switch (state_)
	{
	case PLAY_STATE::STATE_STAY:
		Stay();
		break;
	case PLAY_STATE::STATE_COUNT:
		Count();
		break;
	case PLAY_STATE::STATE_PLAY:
		Play();
		break;
	case PLAY_STATE::STATE_FINISH:
		Finish();
	default:
		break;
	}
}

void SnowConeMaking::Stay()
{
	//1P��2P���ǂ�����A�{�^������������Q�[���X�^�[�g
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, 0))
	{
		GetComponent<Image>(explanationNum_).SetAlpha(0.5f);
		copuntFlag_ ^= 0b0001;
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, 1))
	{
		GetComponent<Image>(explanationNum2_).SetAlpha(0.5f);
		copuntFlag_ ^= 0b0010;
	}

	if (copuntFlag_ == 0b0011)
	{
		GetComponent<Image>(explanationNum_).SetAlpha(0);
		GetComponent<Image>(explanationNum2_).SetAlpha(0);
		state_ = PLAY_STATE::STATE_COUNT;
		time_->SetSecond(3.0f);
		time_->UnLock();
	}
}

void SnowConeMaking::Count()
{
	//�Q�[���J�n�܂ł̃J�E���g�_�E�����s��
	GetComponent<Text>(timeText_).SetText(std::to_string(time_->GetSeconds<int>()));
	
	//�J�E���g�_�E�����I�������e�I�u�W�F�N�g�𓮂���
	if (time_->GetSeconds<float>() < 0)
	{
		FindChild("SnowCone_Order")->SetActive(true);
		FindChild("SnowCone_Table")->SetActive(true);
		FindChild("SnowConeMaker_Shave")->SetUpdate(true);
		FindChild("SnowConeMaker_Topping")->SetUpdate(true);
		//�J�E���g�_�E���p�e�L�X�g���폜
		RemoveComponent<Text>(timeText_);
		//���Ԃ�ݒ�
		time_->SetSecond<float>(PLAY_COUNT);
		state_ = PLAY_STATE::STATE_PLAY;
	}
}

void SnowConeMaking::Play()
{
	//�������Ԃ̃v���O���X�o�[�����炷
	GetComponent<Image>(progressImageNum_).SetSize({ PROGRESS_DEFAULT.x * (time_->GetSeconds<float>()/ PLAY_COUNT),
													 PROGRESS_DEFAULT.y,
													 PROGRESS_DEFAULT.z });
	if (time_->GetSeconds<float>() < 0)
	{
		((SnowCone_Order*)FindChild("SnowCone_Order"))->SendResultData();
		InterSceneData::AddData<int>("ResultData", scoreManager_.GetScore());
		GameFinish(true);
		state_ = PLAY_STATE::STATE_FINISH;
		//time_->SetSecond(1.0f);

	}
}

//void SnowConeMaking::Finish()
//{
//	float ratio = time_->GetSeconds<float>();
//	if (ratio <= 0.0f)
//	{
//		newSceneManager::ChangeScene(SCENE_ID::RESULT);
//	}
//}

void SnowConeMaking::AddCup(SnowCone_Cup* cup)
{
	//�����X���X�g�b�N����
	if (cupList_.size() < STOCK_LIMIT)
	{
		cupList_.push_back(cup);
		
			//cup->GetTransform()->position_ = XMLoadFloat3(&cupPos[i]);
		std::string size = ((SnowCone_Order*)FindChild("SnowCone_Order"))->GetSizeString(cup->GetConeSize());
			GetComponent<Text>(shavedCupSize_[cupList_.size()-1]).SetText(size);
			GetComponent<Image>(shavedCupList_[cupList_.size()-1]).SetAlpha(1);
	}
	//�J�b�v�̃X�g�b�N��������������
	else
	{
		cup->RemoveIce();
		cup->KillMe();
	}
}

void SnowConeMaking::ScoreUpdate(int score)
{
	//�X�R�A�̍X�V
	scoreManager_.ScoreUpdate(score);
}

void SnowConeMaking::Evaluation(float size, int syrup, int topping)
{
	//�����X�������ƍ����Ă��邩�m�F
	((SnowCone_Order*)FindChild("SnowCone_Order"))->Judge(size, syrup, topping);
}

SnowCone_Cup* SnowConeMaking::GetCup()
{
	SnowCone_Cup* cup=nullptr;
	//�X�g�b�N���Ă邩���X�������Ă���
	if (cupList_.empty() == false)
	{
		if (cupList_[0]->IsEasing() == true)
			return cup;

		cup = cupList_[0];
		GetComponent<Image>(shavedCupList_[cupList_.size() - 1]).SetAlpha(0);
		GetComponent<Text>(shavedCupSize_[cupList_.size() - 1]).SetText("");
		cupList_.erase(cupList_.begin());
		cupList_.resize(cupList_.size());

		//�X�g�b�N�̕\���X�V
		for (int i = 0;i<cupList_.size();i++)
		{
			std::string size = ((SnowCone_Order*)FindChild("SnowCone_Order"))->GetSizeString(cupList_[i]->GetConeSize());
			GetComponent<Text>(shavedCupSize_[i]).SetText(size);
		}
		return cup;
	}
	else
	return nullptr;
}
void SnowConeMaking::StaticUpdate()
{
	Pause();
}

void SnowConeMaking::NotifiedUpdateT()
{
	time_->UnLock();
}

void SnowConeMaking::NotifiedUpdateF()
{
	time_->Lock();
}


void SnowConeMaking::Release()
{
}
