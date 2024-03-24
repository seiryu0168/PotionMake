#include "P_MP_OutingUI_ActionText.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_OutingUI_ActionText::P_MP_OutingUI_ActionText(Object* parent)
	:GameObject(parent,"P_MP_OutingUI_ActionText")
{
}

P_MP_OutingUI_ActionText::~P_MP_OutingUI_ActionText()
{
}

void P_MP_OutingUI_ActionText::Initialize()
{
	Text actionText(this);
	actionText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	actionText.SetText("çÃèWÇ…èoÇ©ÇØÇÈ\nîÑÇËÇ…çsÇ≠");
	actionText.SetPosition({ 700,500 });
	AddComponent<Text>(actionText);
}

void P_MP_OutingUI_ActionText::Start()
{
}

void P_MP_OutingUI_ActionText::Update()
{
}

void P_MP_OutingUI_ActionText::Release()
{
}
