#include "PotionStock.h"
#include "P_MP_PotionManagerUI_DisposeStockUI.h"
#include "P_MP_PotionManagerUI_SellStockUI.h"
#include "P_MP_PotionManagerUI_PotionStockUI.h"
#include "PotionMenu.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/DirectX_11/Input.h"
#include "../../Engine/Systems/TextSystem.h"
namespace
{
	XMFLOAT3 PotionColorArray[5] = { {238.0f / 255.0f,131.0f / 255.0f,111.0f / 255.0f},//�_�炩���Ԍn�̐F
									 {193.0f / 255.0f,237.0f / 255.0f,111.0f / 255.0f},//�_�炩�����Όn�̐F
									 {111.0f / 255.0f,237.0f / 255.0f,181.0f / 255.0f},//�_�炩���Όn�̐F
									 {111.0f / 255.0f,143.0f / 255.0f,237.0f / 255.0f},//�_�炩�����n�̐F
									 {231.0f / 255.0f,111.0f / 255.0f,237.0f / 255.0f}//�_�炩�����n�̐F 
	};
}

PotionStock::PotionStock(Object* parent)
	:GameObject(parent,"PotionStock"),
	havePotion_(false),
	potionNum_(-1),
	potionImageNum_(-1),
	potionColor_({0,0,0}),
	isSelect_(false),
	isCountDown_(false),
	isConfirm_(false),
	confirmImageNum_(-1),
	selectedSlot_(SelectSlot::None),
	time_(0)
{

}

PotionStock::~PotionStock()
{
}

void PotionStock::Initialize()
{
	//�w�i�摜
	Image potionStockImage(this);
	potionStockImage.Load("Assets/Image/ItemBaseImage.png");
	potionStockImage.SetColor(0.8f);
	potionStockImage.SetLayer(0);
	AddComponent<Image>(potionStockImage);

	XMFLOAT3 imagePos = potionStockImage.GetPositionAtPixel();
	//�X�e�[�^�X
	Text statusText(this);
	statusText.SetTextSize(25);
	statusText.SetText("");
	//statusText.SetLayer(1);
	statusText.isDraw_ = false;
	statusText.SetRect({ 0,0,60,30 });
	statusText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	AddComponent<Text>(statusText);
}

void PotionStock::Start()
{
	disposeUI_ = (P_MP_PotionManagerUI_DisposeStockUI*)FindObject("P_MP_PotionManagerUI_DisposeStockUI");
	sellUI_ = (P_MP_PotionManagerUI_SellStockUI*)FindObject("P_MP_PotionManagerUI_SellStockUI");

	if (selectedSlot_ == SelectSlot::Sell)
		AddSellPotion();
}

void PotionStock::Update()
{
	if (isCountDown_)
	{
		time_ += 0.017f;
		if (time_ >= 0.3f)
		{
			isCountDown_ = false;
			time_ = 0;
			((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->SetEnablePotionStock(true);
		}
	}
	if (GetComponent<Image>().IsHitCursor())
	{
		GetComponent<Image>().SetColor(1.0f);
		if (Input::IsMouseButtonDown(0) && isSelect_)
		{
			GameObject* potionMenu = Instantiate<PotionMenu>(this);
			potionMenu->GetComponent<Image>().SetPosition({ 0.5f,0,0 });
			((PotionMenu*)potionMenu)->CreateMenu(potionNum_, potionName_, potionColor_, isConfirm_);
			//((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->CreatePotionMenu(potionNum_, potionName_, potionColor_);
			((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->SetEnablePotionStock(false);

			//sellUI_->AddSellPotion(potionNum_, potionName_, potionColor_);
		}
	}
	else
		GetComponent<Image>().SetColor(0.8f);
}

void PotionStock::SetPotionColor()
{
	bool isMax_ = false;
	
	//�ł��l���傫���X�e�[�^�X��T���ă|�[�V�����̐F��ς���
	for (int i = 4; i > -1; i--)
	{
		float colorRatio = 1.0f;
		for (int j=0;j<4;j++)
		{
			if ((int)potionStatus_[j]==i)
			{
				//colorRatio = 1/(PotionColorArray[j].x + PotionColorArray[j].y + PotionColorArray[j].z);
				
				//�F�𑫂�
				potionColor_.x += PotionColorArray[j].x * colorRatio;
				potionColor_.y += PotionColorArray[j].y * colorRatio;
				potionColor_.z += PotionColorArray[j].z * colorRatio;
				colorRatio *=0.13f;
				isMax_ = true;
			}
		}
		if (isMax_)
			break;
	}
	GetComponent<Image>(potionImageNum_).SetColor(potionColor_);
}

void PotionStock::SetPotionStatus_(int potionNum, const std::string& name, bool isSale,int topStatus, int price, const XMFLOAT3& potionColor, float sts0, float sts1, float sts2, float sts3, float sts4)
{
	//�|�[�V�����f�[�^��ݒ�
	potionNum_ = potionNum;
	potionName_ = name;
	potionStatus_.push_back(sts0);
	potionStatus_.push_back(sts1);
	potionStatus_.push_back(sts2);
	potionStatus_.push_back(sts3);
	potionStatus_.push_back(sts4);
	topStatus_ = topStatus;
	price_ = price;
	potionColor_ = potionColor;
	havePotion_ = true;

	GetComponent<Image>().SetColor(1);
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	
	//�|�[�V������\��
	Image potionBaseImage(this);
	potionBaseImage.Load("Assets/Image/Potion_BaseImage.png");
	//potionBaseImage.SetLayer(0);
	potionBaseImage.SetPosition(pos);
	potionBaseImage.SetColor(potionColor);
	potionBaseImage.SetSize({0.25f,0.25,0});
	potionImageNum_ = AddComponent<Image>(potionBaseImage);

	Image potionEdgeImage(this);
	potionEdgeImage.Load("Assets/Image/Potion_EdgeImage.png");
	//potionEdgeImage.SetLayer(1);
	potionEdgeImage.SetPosition(pos);
	potionEdgeImage.SetSize({0.25f,0.25,0});
	AddComponent<Image>(potionEdgeImage);

	pos = potionBaseImage.GetPositionAtPixel();
	GetComponent<Text>().SetPosition({ pos.x - 25, pos.y-5});

	if (isSale)
		selectedSlot_ = SelectSlot::Sell;
	isSelect_ = true;

	//�F��ݒ�
	//SetPotionColor();
}

void PotionStock::AddSellPotion()
{
	//�̔��g�ɒǉ�����
	sellUI_->AddSellPotion(potionNum_, potionName_, potionColor_);
	
	//����\�ɂȂ�܂ł̃J�E���g�_�E�����J�n
	isCountDown_ = true;
	
	//�m��
	isConfirm_ = true;
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	selectedSlot_ = SelectSlot::Sell;
	
	//���ɉ摜������Ȃ�\��������
	if (confirmImageNum_ != -1)
	{
		GetComponent<Text>().SetText("�̔�");
		GetComponent<Text>().isDraw_ = true;
		GetComponent<Image>(confirmImageNum_).SetAlpha(1);
		return;
	}
	GetComponent<Text>().SetText("�̔�");
	GetComponent<Text>().isDraw_ = true;
	//���삪�m�肵�����̉摜������
	Image confirmImage(this);
	confirmImage.Load("Assets/Image/ItemSlotImage.png");
	//confirmImage.SetLayer(1);
	confirmImage.SetPosition(pos);
	confirmImage.SetSize({ 1,0.3f,0 });
	confirmImageNum_ = AddComponent<Image>(confirmImage);
}

void PotionStock::AddDisposePotion()
{
	//�j���g�ɒǉ�����
	disposeUI_->AddDisposePotion(potionNum_, potionName_, potionColor_);
	
	//����\�ɂȂ�܂ł̃J�E���g�_�E�����J�n
	isCountDown_ = true;
	
	//�m��
	isConfirm_ = true;
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	selectedSlot_ = SelectSlot::Dispose;
	
	//���ɉ摜������Ȃ�\��������
	if (confirmImageNum_ != -1)
	{
		GetComponent<Text>().SetText("�j��");
		GetComponent<Text>().isDraw_ = true;
		GetComponent<Image>(confirmImageNum_).SetAlpha(1);
		return;
	}
	GetComponent<Text>().SetText("�j��");
	GetComponent<Text>().isDraw_ = true;
	//���삪�m�肵�����̉摜
	Image confirmImage(this);
	confirmImage.Load("Assets/Image/UIBaseImage5.png");
	//confirmImage.SetLayer(1);
	confirmImage.SetPosition(pos);
	confirmImage.SetSize({ 2,0.6f,0 });
	confirmImageNum_ = AddComponent<Image>(confirmImage);
}

void PotionStock::SubPotion()
{
	if (selectedSlot_ == SelectSlot::Sell)
	{
		sellUI_->SubSellPotion(potionNum_);
		GetComponent<Image>(confirmImageNum_).SetAlpha(0);
	}
	else if (selectedSlot_ == SelectSlot::Dispose)
	{
		disposeUI_->SubDisposePotion(potionNum_);
		GetComponent<Image>(confirmImageNum_).SetAlpha(0);
	}
	GetComponent<Text>().isDraw_ = false;
	selectedSlot_ = SelectSlot::None;
	isConfirm_ = false;
	isCountDown_ = true;

}

void PotionStock::SetEnablePotionStock(bool enable)
{
	((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->SetEnablePotionStock(enable);
}

void PotionStock::Release()
{
}
