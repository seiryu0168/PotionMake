#pragma once
#include"../../UIBase.h"
/// <summary>
/// �O�o����UI
/// </summary>
class Play_ManagementPart_OutingUI : public UIBase
{
private:
public:
	Play_ManagementPart_OutingUI(Object* parent);
	~Play_ManagementPart_OutingUI();
	void Initialize() override;
	void Update() override;
	void Release() override;
};
