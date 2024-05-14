#include "MenuUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"

MenuUI::MenuUI(Object* parent, const std::string& name)
	:UIBase(parent,name),
	isClickedButton_(false)
{
}

void MenuUI::SetButton(const std::string& imageName, const std::string& msg, const XMFLOAT3& pos)
{
	buttonPos_ = pos;
	Image btnImage(this);
	btnImage.Load(imageName);
	btnImage.SetPosition(pos);
	btnImage.SetRotation({ 0,0,180 });
	//save.SetSize({ 5,2,0 });
	AddComponent<Image>(btnImage);
	XMFLOAT3 textPos = btnImage.GetPositionAtPixel();
	Text saveText(this);
	saveText.SetText(msg);
	saveText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(saveText);
}

void MenuUI::SetButtonPosition(const XMFLOAT3& pos)
{
	buttonPos_ = pos;
	GetComponent<Image>().SetPosition(pos);
	XMFLOAT3 txtPos = GetComponent<Image>().GetPositionAtPixel();
	GetComponent<Text>().SetPosition({ txtPos.x + 200,txtPos.y - 50 });
}
