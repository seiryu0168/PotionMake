#pragma once
#include"Engine/GameObject/GameObject.h"
class Play_ManagementPart_BaseUI : public GameObject
{
private:

	int UINum_;
public:
	Play_ManagementPart_BaseUI(Object* parent);
	~Play_ManagementPart_BaseUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
	void AccessUI(int uiNum);
	void DisplayAction(std::string action, bool isDisplay);
	int GetUINum() { return UINum_; }
};

