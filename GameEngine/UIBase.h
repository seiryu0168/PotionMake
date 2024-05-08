#pragma once
#include"Engine/GameObject/GameObject.h"
class UIBase : public GameObject
{
private:
	int UINum_;
	std::string uiName_;
	bool isOpenUI_;
	int currentOpenUINum_;
public:
	UIBase(Object* parent,std::string uiName);
	~UIBase();

	int GetUINumber() { return UINum_; }
	void SetOpenUIFlag(bool flag) { isOpenUI_ = flag; }
	bool GetOpenUIFlag() { return isOpenUI_; }
};

