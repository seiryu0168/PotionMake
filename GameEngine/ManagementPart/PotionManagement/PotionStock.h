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
	void SetPotionStatus_(int potionNum, const std::string& name,bool isSale, int sts0, int sts1, int sts2, int sts3, int sts4);
	int GetPotionNumber() { return potionNum_; }
	void AddSellPotion();
	void AddDisposePotion();
	void SubPotion();
	void SetEnablePotionStock(bool enable);
	const std::string& GetPotionName() { return potionName_; }
	const std::vector<float>& GetPotionStatus() { return potionStatus_; }
	SelectSlot GetSelectedSlot() { return selectedSlot_; }
	void Release() override;

private:
	SelectSlot selectedSlot_;
	int potionNum_;
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

