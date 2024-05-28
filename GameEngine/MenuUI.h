#pragma once
#include"UIBase.h"

/// <summary>
/// メニューUIの基底クラス
/// </summary>
class MenuUI : public UIBase
{
	bool isClickedButton_;
public:
	XMFLOAT3 buttonPos_;
	MenuUI(Object* parent, const std::string& name);
	~MenuUI() {};
	void SetButton(const std::string& imageName, const std::string& msg,const XMFLOAT3& pos);
	void SetButtonPosition(const XMFLOAT3& pos);
	void SetClickFlag(bool flag) { isClickedButton_ = flag; }
	bool IsClickButton() { return isClickedButton_; }
};