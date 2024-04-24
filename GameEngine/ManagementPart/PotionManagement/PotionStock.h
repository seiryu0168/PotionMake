#pragma once
#include"../../Engine/GameObject/GameObject.h"

class P_MP_PotionManagerUI_DisposeStockUI;
class P_MP_PotionManagerUI_SellStockUI;

/// <summary>
/// ポーションの在庫を表示
/// </summary>
class PotionStock : public GameObject
{

public:
	enum class SelectSlot
	{
		None = 0,
		Sell,
		Dispose,
	};

	PotionStock(Object* parent);
	~PotionStock();

	bool isSelect_;
	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetPotionColor();
	void SetPotionStatus_(int potionNum, const std::string& name,bool isSale,int topStatus,int price,const XMFLOAT3& potionColor, float sts0, float sts1, float sts2, float sts3, float sts4);
	void AddSellPotion();
	void AddDisposePotion();
	void SubPotion();
	void SetEnablePotionStock(bool enable);
	void Release() override;
	
	int						  GetPotionNumber() { return potionNum_; }
	const std::string&		  GetPotionName()   { return potionName_; }
	SelectSlot				  GetSelectedSlot() { return selectedSlot_; }
	int						  GetTopStatus()    { return topStatus_; }
	int						  GetPrice()		{ return price_; }
	const std::vector<float>& GetPotionStatus() { return potionStatus_; }
	const XMFLOAT3&			  GetPotionColor()  { return potionColor_; }


private:
	SelectSlot selectedSlot_;
	int potionNum_;
	int topStatus_;
	int price_;
	std::string potionName_;
	std::vector<float> potionStatus_;
	XMFLOAT3 potionColor_;
	bool havePotion_;
	bool isConfirm_;
	bool isCountDown_;
	int potionImageNum_;
	int confirmImageNum_;
	P_MP_PotionManagerUI_DisposeStockUI* disposeUI_;
	P_MP_PotionManagerUI_SellStockUI* sellUI_;

	float time_;

};

