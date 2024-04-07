#include "PotionStock.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"P_MP_PotionManagerUI_DisposeStockUI.h"
#include"P_MP_PotionManagerUI_SellStockUI.h"
#include"P_MP_PotionManagerUI_PotionStockUI.h"
namespace
{
	XMFLOAT3 PotionColorArray[5] = { {238.0f / 255.0f,131.0f / 255.0f,111.0f / 255.0f},//è_ÇÁÇ©Ç¢ê‘ånÇÃêF
									 {193.0f / 255.0f,237.0f / 255.0f,111.0f / 255.0f},//è_ÇÁÇ©Ç¢â©óŒånÇÃêF
									 {111.0f / 255.0f,237.0f / 255.0f,181.0f / 255.0f},//è_ÇÁÇ©Ç¢óŒånÇÃêF
									 {111.0f / 255.0f,143.0f / 255.0f,237.0f / 255.0f},//è_ÇÁÇ©Ç¢ê¬éáånÇÃêF
									 {231.0f / 255.0f,111.0f / 255.0f,237.0f / 255.0f}//è_ÇÁÇ©Ç¢éáånÇÃêF 
	};
}

PotionStock::PotionStock(Object* parent)
	:GameObject(parent,"PotionStock"),
	havePotion_(false),
	potionImageNum_(-1),
	potionColor_({0,0,0}),
	isSelect_(true)
{

}

PotionStock::~PotionStock()
{
}

void PotionStock::Initialize()
{
	Image potionStockImage(this);
	potionStockImage.Load("Assets/Image/ItemSlotImage.png");
	potionStockImage.SetLayer(0);
	AddComponent<Image>(potionStockImage);
}

void PotionStock::Start()
{
	disposeUI_ = (P_MP_PotionManagerUI_DisposeStockUI*)FindObject("P_MP_PotionManagerUI_DisposeStockUI");
	sellUI_ = (P_MP_PotionManagerUI_SellStockUI*)FindObject("P_MP_PotionManagerUI_SellStockUI");
}

void PotionStock::Update()
{
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>().IsHitCursor()&&isSelect_)
	{
		((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->CreatePotionMenu(potionNum_, potionName_, potionColor_);
		((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->SetEnablePotionStock(false);
		
		//sellUI_->AddSellPotion(potionNum_, potionName_, potionColor_);
	}
}

void PotionStock::SetPotionColor()
{
	bool isMax_ = false;
	//XMFLOAT3 color = { 0,0,0 };
	
	//ç≈Ç‡ílÇ™ëÂÇ´Ç¢ÉXÉeÅ[É^ÉXÇíTÇµÇƒÉ|Å[ÉVÉáÉìÇÃêFÇïœÇ¶ÇÈ
	for (int i = 4; i > -1; i--)
	{
		float colorRatio = 1.0f;
		for (int j=0;j<4;j++)
		{
			if ((int)potionStatus_[j]==i)
			{
				//colorRatio = 1/(PotionColorArray[j].x + PotionColorArray[j].y + PotionColorArray[j].z);
				
				//êFÇë´Ç∑
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

void PotionStock::SetPotionStatus_(int potionNum, const std::string& name, int sts0, int sts1, int sts2, int sts3, int sts4)
{
	potionNum_ = potionNum;
	potionName_ = name;
	potionStatus_.push_back(sts0);
	potionStatus_.push_back(sts1);
	potionStatus_.push_back(sts2);
	potionStatus_.push_back(sts3);
	potionStatus_.push_back(sts4);
	havePotion_ = true;

	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	//Image potionBackImage(this);
	//potionBackImage.Load("Assets/Image/Potion_BackImage.png");
	//potionBackImage.SetLayer(0);
	//potionBackImage.SetPosition(pos);
	//potionBackImage.SetSize({0.25f,0.25,0});
	//AddComponent<Image>(potionBackImage);

	Image potionBaseImage(this);
	potionBaseImage.Load("Assets/Image/Potion_BaseImage.png");
	potionBaseImage.SetLayer(0);
	potionBaseImage.SetPosition(pos);
	potionBaseImage.SetSize({0.25f,0.25,0});
	potionImageNum_ = AddComponent<Image>(potionBaseImage);

	Image potionEdgeImage(this);
	potionEdgeImage.Load("Assets/Image/Potion_EdgeImage.png");
	potionEdgeImage.SetLayer(1);
	potionEdgeImage.SetPosition(pos);
	potionEdgeImage.SetSize({0.25f,0.25,0});
	AddComponent<Image>(potionEdgeImage);

	SetPotionColor();
}

void PotionStock::Release()
{
}
