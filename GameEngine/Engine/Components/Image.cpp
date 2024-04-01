#include "Image.h"
#include"../ResourceManager/ImageManager_ECSver.h"
#include"../DirectX_11/Direct3D.h"
#include"../GameObject/CameraManager.h"
#include "../DirectX_11/Input.h"
#include "../ResourceManager/ImageMediationer.h"

XMFLOAT3 Image::ConvertToRatio(XMFLOAT3 pos)
{
	pos.x = pos.x / (float)Direct3D::GetScreenWidth();
	pos.y = pos.y / (float)Direct3D::GetScreenHeight();
	return pos;
}

XMFLOAT3 Image::ConvertToPixel(XMFLOAT3 pos)
{
	XMFLOAT2 halfScreen = { Direct3D::GetScreenWidth() / 2.0f,Direct3D::GetScreenHeight() / 2.0f };
	pos.x = halfScreen.x+((pos.x * halfScreen.x));
	pos.y = halfScreen.y + ((-pos.y * halfScreen.y));

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

	if (tab != "")
		transform_ = ImageMediationer::Load(name, tab, pSprite_.use_count());

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
	SetColor({ color, color, color });
}

void Image::SetColor(const XMFLOAT3& color) noexcept
{
	color_.x = color.x;
	color_.y = color.y;
	color_.z = color.z;
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
	XMFLOAT3 mousePos = StoreFloat3(Input::GetMousePosition());
    float wid = (pSprite_->GetSize().x * transform_.scale_.x / 2);
    float hgt = (pSprite_->GetSize().y * transform_.scale_.y / 2);
    float Left = (XMVectorGetX(transform_.position_) + 1) * (Direct3D::GetScreenWidth() / 2.0f) - wid;
    float Right = (XMVectorGetX(transform_.position_) + 1) * (Direct3D::GetScreenWidth() / 2.0f) + wid;
    float Top = (-XMVectorGetY(transform_.position_) + 1) * (Direct3D::GetScreenHeight() / 2.0f) - hgt;
    float Bottom = (-XMVectorGetY(transform_.position_) + 1) * (Direct3D::GetScreenHeight() / 2.0f) + hgt;
    if (Left <= mousePos.x && mousePos.x <= Right &&
        Top <= mousePos.y && mousePos.y <= Bottom)
    {
        return true;
    }
    return false;
}
