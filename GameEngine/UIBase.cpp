#include "UIBase.h"

UIBase::UIBase(Object* parent, std::string uiName)
	:GameObject(parent,uiName),
	isOpenUI_(false)
{
}

UIBase::~UIBase()
{
}
