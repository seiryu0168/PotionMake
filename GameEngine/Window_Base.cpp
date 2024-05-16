#include "Window_Base.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
Window_Base::Window_Base(Object* parent, const std::string& name)
	:GameObject(parent,name),
	uiPos_({0,0,0})
{
}

void Window_Base::CreateBase(const std::string& backImage, const XMFLOAT3& uiPos, XMFLOAT2 windowSize,float edgeSize)
{
	uiPos_ = uiPos;
	XMFLOAT3 baseImageSize;
	XMFLOAT3 imageRatio;
	Image uiBaseImage(this);
	uiBaseImage.Load(backImage);
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 16 * windowSize.x,16 * windowSize.y,0 });
	baseImageSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	baseImageSize = { baseImageSize.x / (Direct3D::GetScreenWidth()),
				   baseImageSize.y / (Direct3D::GetScreenHeight()),0 };

	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + baseImageSize.y,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x,edgeSize,0 });
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - baseImageSize.y,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x,edgeSize,0 });
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ uiPos_.x + baseImageSize.x,uiPos_.y,0 });
	uiHeightEdgeImage1.SetSize({ edgeSize,imageRatio.y,0 });
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ uiPos_.x - baseImageSize.x,uiPos_.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y,0 });
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ uiPos_.x + baseImageSize.x,uiPos_.y + baseImageSize.y,0 });
	uiCornerImage1.SetSize({ edgeSize,edgeSize,0 });
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ uiPos_.x + baseImageSize.x,uiPos_.y - baseImageSize.y,0 });
	uiCornerImage2.SetSize({ edgeSize,edgeSize,0 });
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ uiPos_.x - baseImageSize.x,uiPos_.y - baseImageSize.y,0 });
	uiCornerImage3.SetSize({ edgeSize,edgeSize,0 });
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ uiPos_.x - baseImageSize.x,uiPos_.y + baseImageSize.y,0 });
	uiCornerImage4.SetSize({ edgeSize,edgeSize,0 });
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void Window_Base::CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str, float textSize, const XMINT3& color)
{
	titlePos_ = { pos.x,pos.y,0 };
	XMINT2 windowSize = Direct3D::GetWindwSize();
	Text craftUIText(this);
	craftUIText.SetText(str);
	craftUIText.SetTextSize(textSize);
	float rectSize = craftUIText.GetTextSize() * str.size() * 0.5f;
	TEXT_RECT rect = { 0,0,rectSize + diff.x,(float)craftUIText.GetTextSize() + diff.y };
	XMFLOAT2 txtPos = { 0,0 };
	txtPos.x = (pos.x * windowSize.x * 0.5f) + (windowSize.x * 0.5f);
	txtPos.y = (-pos.y * windowSize.y * 0.5f) + (windowSize.y * 0.5f);

	txtPos.x -= (rect.right * 0.5f);
	craftUIText.SetRect(rect);
	craftUIText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
	craftUIText.SetPosition({ txtPos.x, txtPos.y });
	AddComponent<Text>(craftUIText);

	XMFLOAT2 imagePos = { pos.x ,pos.y - rect.bottom / windowSize.y };
	Image base(this);
	base.Load("Assets/Image/UIBaseImage3.png");
	base.SetColorInt(color);
	base.SetSize({ 0.015625f * rect.right,0.015625f * rect.bottom,0 });
	base.SetPosition({ imagePos.x,imagePos.y,0 });
	XMFLOAT3 size = base.GetSizeAtPixel();
	//XMFLOAT2 distance = { size.x / Direct3D::GetScreenWidth(),size.y / Direct3D::GetScreenHeight() };

	float distance = rect.right / windowSize.x;
	Image start(this);
	start.Load("Assets/Image/UILong04_Start.png");
	start.SetColorInt(color);
	start.SetSize({ size.y / 256,size.y / 256,0.0f });
	//start.SetRotation({ 0,0,180 });
	start.SetPosition({ imagePos.x - distance - 0.03f,imagePos.y,0 });
	titleImageNum_[0] = AddComponent<Image>(start);

	Image end(this);
	end.Load("Assets/Image/UILong04_End.png");
	end.SetColorInt(color);
	end.SetSize({ size.y / 256,size.y / 256,0.0f });
	end.SetPosition({ imagePos.x + distance + 0.03f,imagePos.y,0 });
	titleImageNum_[2] = AddComponent<Image>(end);

	titleImageNum_[1] = AddComponent<Image>(base);
}

void Window_Base::ChangeTitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str, float textSize, const XMINT3& color)
{
	titlePos_ = { pos.x,pos.y,0 };
	XMINT2 windowSize = Direct3D::GetWindwSize();
	Text& txt = GetComponent<Text>();
	txt.SetText(str);
	txt.SetTextSize(textSize);
	float rectSize = txt.GetTextSize() * str.size() * 0.5f;
	TEXT_RECT rect = { 0,0,rectSize + diff.x,(float)txt.GetTextSize() + diff.y };
	XMFLOAT2 txtPos = { 0,0 };
	txtPos.x = (pos.x * windowSize.x * 0.5f) + (windowSize.x * 0.5f);
	txtPos.y = (-pos.y * windowSize.y * 0.5f) + (windowSize.y * 0.5f);

	txtPos.x -= (rect.right * 0.5f);
	txt.SetRect(rect);
	txt.SetPosition({ txtPos.x, txtPos.y });
	XMFLOAT2 imagePos = { pos.x,pos.y - rect.bottom / Direct3D::GetScreenHeight() };
	float distance = rect.right / Direct3D::GetScreenWidth();
	Image& img_start = GetComponent<Image>(titleImageNum_[0]);
	Image& img_base = GetComponent<Image>(titleImageNum_[1]);
	Image& img_end = GetComponent<Image>(titleImageNum_[2]);

	img_base.SetColorInt(color);
	img_base.SetPosition({ imagePos.x,imagePos.y,0 });
	img_base.SetSize({ 0.015625f * rect.right,0.015625f * rect.bottom,0 });
	float baseSizeY = img_base.GetSizeAtPixel().y;

	img_start.SetColorInt(color);
	img_start.SetPosition({ imagePos.x - distance - 0.03f,imagePos.y,0 });
	img_start.SetSize({ baseSizeY / 256,baseSizeY / 256,0 });
	img_end.SetColorInt(color);
	img_end.SetPosition({ imagePos.x + distance + 0.03f,imagePos.y,0 });
	img_end.SetSize({ baseSizeY / 256,baseSizeY/256,0 });
}
