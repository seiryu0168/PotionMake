#pragma once
#include"../Engine/GameObject/GameObject.h"

class Player_ManagementPart;

/// <summary>
/// 経営パートの基本的な動作を表示するUI
/// ポーション制作、管理、外出等のアクションを表示
/// </summary>
class Play_ManagementPart_BaseUI : public GameObject
{
private:
	int UINum_;
	bool isAccessUI_;
	bool isTutorial_;
	Player_ManagementPart* player_;
	int hAudio_UIOpen_;
public:
	Play_ManagementPart_BaseUI(Object* parent);
	~Play_ManagementPart_BaseUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void AccessUI(int uiNum);
	void SetAccessUIFlag(bool flag) { isAccessUI_ = flag; }
	void SetUIOpenFlag(bool flag);
	bool IsAccessUI() { return isAccessUI_; }
	void DisplayAction(std::string action, bool isDisplay);
	int  GetUINum() { return UINum_; }
	void CloseFirstTutorialButton();
	void EnableTutorialUI();
	void InvalidTutorialUI();
	void Release() override;
};

