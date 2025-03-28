#include "Image.h"
#include"../ResourceManager/ImageManager_ECSver.h"
#include"../DirectX_11/Direct3D.h"
#include"../GameObject/CameraManager.h"
#include "../DirectX_11/Input.h"
#include "../ResourceManager/ImageMediationer.h"

XMFLOAT3 Image::ConvertToRatio(XMFLOAT3 pos)
{
	XMINT2 window = Direct3D::GetWindwSize();
	pos.x = pos.x / window.x;//(float)Direct3D::GetScreenWidth();
	pos.y = pos.y / window.y;//(float)Direct3D::GetScreenHeight();
	return pos;
}

XMFLOAT3 Image::ConvertToPixel(XMFLOAT3 pos)
{
	//XMINT2 halfScreen =  {Direct3D::GetScreenWidth(),Direct3D::GetScreenHeight()};
	XMINT2 halfScreen = Direct3D::GetWindwSize();//{Direct3D::GetScreenWidth(),Direct3D::GetScreenHeight()};
	int diff = (Direct3D::GetScreenHeight() - halfScreen.y);
	//halfScreen.x = halfScreen.x * 0.5f;
	//halfScreen.y = halfScreen.y * 0.5f;
	pos.x = halfScreen.x * 0.5f + ((pos.x * halfScreen.x*0.5f));
	pos.y = halfScreen.y * 0.5f + (-pos.y * halfScreen.y*0.5f);
	//pos.y = (halfScreen.y*0.5f + ((-pos.y * halfScreen.y*0.5f)))-diff;

	return pos;
}

XMFLOAT3 Image::ConvertToPixel(XMVECTOR pos)
{
	XMFLOAT3 retPos = StoreFloat3(pos);
	retPos = ConvertToPixel(retPos);
	return retPos;
}

XMFLOAT3 Image::GetPositionAtPixel()
{
	return ConvertToPixel(transform_.position_);
}

XMFLOAT3 Image::GetRatio()
{
	return StoreFloat3(transform_.position_);
}


Image::Image(int cameraNum, int layerNum)
	:alpha_(1.0f),
	rect_({ 0,0,1,1 }),
	color_({ 1,1,1,1 }),
	imageName_(""),
	pSprite_(),
	transform_(),
	drawTargetNumber_(cameraNum),
	layerNum_(layerNum),
	scroll_({ 0,0 }),
	isStatic_(false),
	isDraw_(true)
{
}

Image::Image(GameObject* object,int cameraNum,int layerNum)
	:alpha_(1.0f),
	rect_({ 0,0,1,1 }),
	color_({1,1,1,1}),
	imageName_(""),
	pSprite_(),
	transform_(),
	drawTargetNumber_(cameraNum),
	layerNum_(layerNum),
	scroll_({0,0}),
	isStatic_(false),
	isDraw_(true),
	attachObject_(object)
{
}

Image::~Image()
{
}

bool Image::Load(const std::string& name, const std::string& tab)
{
	imageName_ = name;
	pSprite_ = ImageManager_ECSver::Load(name);
	if(pSprite_==nullptr)
	return false;

	XMFLOAT3 size = pSprite_->GetSize();
	rect_ = { 0,0,(long)size.x,(long)size.y };
	transform_.position_ = XMVectorSet(0, 0, 0, 0);
	transform_.rotate_ = XMVectorSet(0, 0, 0, 0);
	transform_.scale_ = { 1,1,1 };
	//if (tab != "")
	//	transform_ = //ImageMediationer::Load(name, tab, pSprite_.use_count());

	return true;
}

bool Image::StaticLoad(const std::string& name)
{
	imageName_ = name;
	pSprite_ = ImageManager_ECSver::StaticLoad(name);
	if (pSprite_ == nullptr)
		return false;

	XMFLOAT3 size = pSprite_->GetSize();
	rect_ = { 0,0,(long)size.x,(long)size.y };
	isStatic_ = true;
	return true;
}

void Image::SetPosition(const XMFLOAT3& pos)
{
	transform_.position_ = XMLoadFloat3(&pos);
}

void Image::SetPosition(float x, float y)
{
	transform_.position_ = XMVectorSet(x, y, 0, 0);
}

void Image::SetPositionAtPixel(const XMFLOAT3& pos)
{
	XMFLOAT3 p = ConvertToRatio(pos);
	transform_.position_ = XMLoadFloat3(&p);
}
void Image::AddPositionAtPixel(const XMFLOAT3& deltaPos)
{
	XMFLOAT3 p = ConvertToRatio(deltaPos);
	transform_.position_ += XMLoadFloat3(&p);
}


void Image::SetAlpha(float alpha)
{
	alpha_ = alpha;
}

void Image::SetColor(const float color) noexcept
{
	SetColor(XMFLOAT3{ color, color, color });
}

void Image::SetColorInt(const int color) noexcept
{
	color_.x = (float)color / 255;
	color_.y = (float)color / 255;
	color_.z = (float)color / 255;
}

void Image::SetColorInt(const XMINT3& color) noexcept
{
	color_.x = color.x / 255.0f;
	color_.y = color.y / 255.0f;
	color_.z = color.z / 255.0f;
}

void Image::SetColorInt(const XMINT4& color) noexcept
{
	color_.x = color.x / 255.0f;
	color_.y = color.y / 255.0f;
	color_.z = color.z / 255.0f;
	alpha_   = color.w / 255.0f;
}

void Image::SetColor(const XMFLOAT3& color) noexcept
{
	color_.x = color.x;
	color_.y = color.y;
	color_.z = color.z;
}

void Image::SetColor(const XMFLOAT4& color) noexcept
{
	color_.x = color.x;
	color_.y = color.y;
	color_.z = color.z;
	alpha_   = color.w;
}

void Image::SetScroll(const XMFLOAT2& scroll)
{
	scroll_ = scroll;
}

void Image::SetSize(const XMFLOAT3& size)
{
	transform_.scale_ = size;
}

void Image::SetRotation(const XMFLOAT3& rotate)
{
	transform_.RotateEular(rotate);
}

void Image::Draw()
{
	if (isStatic_)
	{
		if (drawTargetNumber_ == CameraManager::GetCurrentCameraNum() || drawTargetNumber_ == -1)
			pSprite_->StaticDraw(transform_, rect_, color_, alpha_, scroll_);
	}
	else
	{
		if (drawTargetNumber_ == CameraManager::GetCurrentCameraNum() || drawTargetNumber_ == -1)
			pSprite_->Draw(transform_, rect_, color_, alpha_, scroll_);
	}
}

void Image::Draw(int layerNum)
{
	if (layerNum != layerNum_)
		return;

	if (isStatic_)
	{
		if (drawTargetNumber_ == CameraManager::GetCurrentCameraNum() || drawTargetNumber_ == -1)
			pSprite_->StaticDraw(transform_, rect_, color_, alpha_, scroll_);
	
	}
	else
	{
		if (drawTargetNumber_ == CameraManager::GetCurrentCameraNum() || drawTargetNumber_ == -1)
			pSprite_->Draw(transform_, rect_, color_, alpha_, scroll_);
	}
}

void Image::SimpleDraw()
{
	if (isStatic_)
			pSprite_->StaticDraw(transform_, rect_, color_, alpha_, scroll_);
	else
			pSprite_->Draw(transform_, rect_, color_, alpha_, scroll_);
}

void Image::SetLayer(int layer)
{
	layerNum_ = layer;
}

bool Image::IsHitCursor()
{
	if (!isDraw_)
		return false;
	XMFLOAT3 mousePos = StoreFloat3(Input::GetMousePosition());
	XMFLOAT3 imagePos = ConvertToPixel(transform_.position_);
    float wid = (pSprite_->GetSize().x * transform_.scale_.x*0.5f);
    float hgt = (pSprite_->GetSize().y * transform_.scale_.y*0.5f);
	int screenHeight = Direct3D::GetScreenHeight();
	int windowHeight = Direct3D::GetWindwSize().y;

	imagePos.y -= (screenHeight*0.5f-windowHeight*0.5f)*((float)mousePos.y/(float)screenHeight);

	float Left = imagePos.x	  - wid;
	float Top = imagePos.y  - hgt;
	float Right = imagePos.x  + wid;
	float Bottom = Top + hgt*2;

    if (Left <= mousePos.x && mousePos.x <= Right &&
        Top <= mousePos.y && mousePos.y <= Bottom)
    {
        return true;
    }
    return false;
}