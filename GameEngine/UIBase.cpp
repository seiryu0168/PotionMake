#include "UIBase.h"

UIBase::UIBase(Object* parent, std::string uiName)
	:GameObject(parent,uiName),
	UINum_(-1),
	uiName_(""),
	isOpenUI_(false),
	currentOpenUINum_(-1)
{
}

UIBase::~UIBase()
{
}
