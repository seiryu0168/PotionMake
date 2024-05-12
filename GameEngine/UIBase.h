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

	void SetUINUmber(int num) { UINum_ = num; }
	int GetUINumber() { return UINum_; }
	void SetUIName(const std::string& name) { uiName_ = name; }
	const std::string& GetUIName() { return uiName_; }
	void SetOpenUIFlag(bool flag) { isOpenUI_ = flag; }
	bool GetOpenUIFlag() { return isOpenUI_; }
	void SetCurrentOpenUINumber(int num) { currentOpenUINum_ = num; }
	int GetCurrentOpenUINumber() { return currentOpenUINum_; }
};

