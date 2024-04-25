#pragma once
#include"../../UIBase.h"
/// <summary>
/// äOèoéûÇÃUI
/// </summary>
class Play_ManagementPart_OutingUI : public UIBase
{
private:
	bool canCloseUI_;
	bool isOuting_;
	float time_;
	float countLimit_;
	int outingNumber_;
public:
	Play_ManagementPart_OutingUI(Object* parent);
	~Play_ManagementPart_OutingUI();
	void Initialize() override;
	void Update() override;
	void Outing(int num);
	void SetOutNumber(int num);
	void SetCloseFlag(bool flag) { canCloseUI_ = flag; }
	void Release() override;
};

