#pragma once
#include"../../UIBase.h"
/// <summary>
/// äOèoéûÇÃUI
/// </summary>
class Play_ManagementPart_OutingUI : public UIBase
{
private:
	bool canCloseUI_;
public:
	Play_ManagementPart_OutingUI(Object* parent);
	~Play_ManagementPart_OutingUI();
	void Initialize() override;
	void Update() override;
	void SetCloseFlag(bool flag) { canCloseUI_ = flag; }
	void Release() override;
};

