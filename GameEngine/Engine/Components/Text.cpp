#include "Text.h"
#include<locale.h>
#include<filesystem>
#include"../GameObject/CameraManager.h"

Text::Text(const int& renderTargetNum)
	:layerNum_(0)
{
	textLength_	   = 0;
	transform2D = { 0,0 };
	layoutRect_ = { 0,0,100,100 };

	pText_		   = L"";
	pColorBrush_   = nullptr;
	//pWriteFactory_ = nullptr;
	pTextFormat_   = nullptr;
	pLayout_	   = nullptr;
		if (renderTargetNum<D2D::GetRenderTargetCount() &&renderTargetNum>=0)
			renderTargetNum_ = renderTargetNum;
		else
			renderTargetNum_ = 0;
	Initialize();

}

Text::Text(const std::string& text, const std::string& fontName, const TEXT_RECT& rect, int renderTargetNum,int layerNum, const DWRITE_FONT_WEIGHT& wight, const DWRITE_FONT_STYLE& style, const DWRITE_FONT_STRETCH& stretch, const ALIGNMENT_TYPE& type)
	:layerNum_(layerNum)
{
	if (renderTargetNum < D2D::GetRenderTargetCount() && renderTargetNum >= 0)
		renderTargetNum_ = renderTargetNum;
	else
		renderTargetNum_ = 0;
	//�t�H���g���p�̔z��p��
	size_t ret;
	FontData data;
	std::filesystem::path txt = text;
	pText_ = txt.wstring();
	std::filesystem::path font = fontName;
	pFontName_ = font.wstring();
	//int a = mbstowcs_s(&ret, (wchar_t*)data.fontName_.c_str(), fontName.length() + 1, fontName.c_str(), fontName.length());
	size_t textSize;

	//�`�悷��e�L�X�g�p�̔z���p�ӂ���
	textLength_ = pText_.length();// +1;

	//���݂̃��P�[���擾
	std::string locale = setlocale(LC_CTYPE, NULL);
	data.fontName_ = pFontName_;
	data.locale_ = (wchar_t*)L"en-us";
	data.pCollection_ = D2D::GetCollection();
	data.fontWaight_ = DWRITE_FONT_WEIGHT_NORMAL;
	data.fontStyle_ = DWRITE_FONT_STYLE_NORMAL;
	data.fontStretch_ = DWRITE_FONT_STRETCH_NORMAL;
	//���P�[������{��ɕύX
	setlocale(LC_CTYPE, "ja-jp");
	//�`�悷��e�L�X�g��string����wstring�ɕϊ�
	//mbstowcs_s(&textSize, (wchar_t*)pText_.c_str(), textLength_, text.c_str(), text.length());
	//���P�[�������ɖ߂�
	setlocale(LC_CTYPE, locale.c_str());
	//�ϊ�����������
	//textLength_ = textSize;
	HRESULT hr;
	hr=SetFont(data);
	//�A���C�����g�ݒ�
	//�`��̂��߂̃u���V�쐬
	hr = D2D::GetRenderTarget(renderTargetNum_)->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pColorBrush_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�J���[�u���V�̍쐬�Ɏ��s:Text.cpp", L"OK", MB_OK);
	}
	//�e�L�X�g�\���̗̈�ݒ�
	layoutRect_ = rect;

	//�e�L�X�g���C�A�E�g�쐬
	hr = D2D::GetDWriteFactory()->CreateTextLayout(pText_.c_str(), (UINT32)textLength_, pTextFormat_, (layoutRect_.right - layoutRect_.left), (layoutRect_.bottom - layoutRect_.top), &pLayout_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�e�L�X�g���C�A�E�g�̍쐬�Ɏ��s:Text.cpp", L"OK", MB_OK);
	}
	SetAlignmentType(type);
	defaultPos_ = { CameraManager::GetCamera(renderTargetNum_).GetViewPort().TopLeftX,CameraManager::GetCamera(renderTargetNum_).GetViewPort().TopLeftY };
	transform2D.x = defaultPos_.x + transform2D.x;
	transform2D.y = transform2D.y + defaultPos_.y;
}
Text::~Text()
{
	//Release();
}

int Text::GetTextSize() const
{
	return (int)pLayout_->GetFontSize();
}

void Text::Release()
{
	SAFE_RELEASE(pTextFormat_);
	//SAFE_RELEASE(pWriteFactory_);
	//SAFE_RELEASE(pColorBrush_);
}

int Text::Load(const std::string& text, const std::string& fontName, const TEXT_RECT& rect, const ALIGNMENT_TYPE& type)
{
	//�t�H���g���p�̔z��p��
	size_t ret;
	FontData data;
	int a=mbstowcs_s(&ret, (wchar_t*)data.fontName_.c_str(), fontName.length() + 1, fontName.c_str(), fontName.length());
	size_t textSize;

	//�`�悷��e�L�X�g�p�̔z���p�ӂ���
	textLength_ = text.length()+1;

	//���݂̃��P�[���擾
	std::string locale = setlocale(LC_CTYPE, NULL);
	
	data.locale_ = (wchar_t*)L"en-us";
	//���P�[������{��ɕύX
	setlocale(LC_CTYPE, "ja-jp");
	//�`�悷��e�L�X�g��string����wstring�ɕϊ�
	mbstowcs_s(&textSize, (wchar_t*)pText_.c_str(), textLength_, text.c_str(), text.length());
	//���P�[�������ɖ߂�
	setlocale(LC_CTYPE, locale.c_str());
	//�ϊ�����������
	textLength_ = textSize;

	//HRESULT hr=DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pWriteFactory_));
	////�e�L�X�g�t�H�[�}�b�g�Ƀt�H���g��ݒ�
	//hr=SetFont(data);
	//if (FAILED(hr))
	//{
	//	return hr;
	//}
	//pWriteFactory_->CreateTextFormat(pFontName_, NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,72.0f, L"ja-jp", &pTextFormat_);
	//�A���C�����g�ݒ�
	HRESULT hr;
	SetAlignmentType(type);
	//�`��̂��߂̃u���V�쐬
	hr=D2D::GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pColorBrush_);
	if (FAILED(hr))
	{
		return hr;
	}
	//�e�L�X�g�\���̗̈�ݒ�
	layoutRect_ = rect;
	
	//�e�L�X�g���C�A�E�g�쐬
	hr=D2D::GetDWriteFactory()->CreateTextLayout(pText_.c_str(), (UINT32)textLength_, pTextFormat_, (layoutRect_.right - layoutRect_.left), (layoutRect_.bottom - layoutRect_.top), &pLayout_);
	if (FAILED(hr))
	{
		return hr;
	}
	SetPosition({ 0, 0 });
	return 0;
}

void Text::Initialize()
{
	//�t�H���g���p�̔z��p��
	//size_t ret;
	FontData data;
	std::wstring fontName= L"Arial";
	std::wstring&& text = L"sumple";
	//size_t textSize;
	pFontName_ = fontName;
	data.fontName_ = fontName;
	data.pCollection_ = D2D::GetCollection();

	//�`�悷��e�L�X�g�p�̔z���p�ӂ���
	textLength_ = text.length() + 1;

	pText_ = text;

	//���݂̃��P�[���擾
	std::string locale = setlocale(LC_CTYPE, NULL);

	data.locale_ = (wchar_t*)L"en-us";
	data.fontWaight_ = DWRITE_FONT_WEIGHT_NORMAL;
	data.fontStyle_ = DWRITE_FONT_STYLE_NORMAL;
	data.fontStretch_=DWRITE_FONT_STRETCH_NORMAL;
	
	HRESULT hr;
	//�e�L�X�g�t�H�[�}�b�g�Ƀt�H���g��ݒ�
	hr = SetFont(data);
	assert(FAILED(hr) == false);
	//�A���C�����g�ݒ�
	//�`��̂��߂̃u���V�쐬
	hr = D2D::GetRenderTarget(renderTargetNum_)->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pColorBrush_);
	assert(FAILED(hr) == false);
	//�e�L�X�g�\���̗̈�ݒ�
	layoutRect_ = {0,0,500,100};

	//�e�L�X�g���C�A�E�g�쐬
	hr = D2D::GetDWriteFactory()->CreateTextLayout(pText_.c_str(), (UINT32)textLength_, pTextFormat_, (layoutRect_.right - layoutRect_.left), (layoutRect_.bottom - layoutRect_.top), &pLayout_);
	assert(FAILED(hr) == false);
	SetAlignmentType(LEFT_TOP);

	defaultPos_ = { CameraManager::GetCamera(renderTargetNum_).GetViewPort().TopLeftX,CameraManager::GetCamera(renderTargetNum_).GetViewPort().TopLeftY };
	transform2D.x = defaultPos_.x + transform2D.x;
	transform2D.y =  transform2D.y+ defaultPos_.y;
}

void Text::Draw()
{
	Direct3D::SetDepthBufferWriteEnable(false);
	D2D::GetRenderTarget()->BeginDraw();
	D2D::GetRenderTarget()->DrawTextLayout(transform2D, pLayout_, pColorBrush_);
	//D2D::GetRenderTarget()->DrawText(pText_, textLength_, pTextFormat_,
	//							    { transform2D.x + layoutRect_.left,
	//								  transform2D.y + layoutRect_.top,
	//								  transform2D.x + layoutRect_.right,
	//								  transform2D.y + layoutRect_.bottom }, pColorBrush_);
	D2D::GetRenderTarget()->EndDraw();
	Direct3D::SetDepthBufferWriteEnable(true);
}

void Text::Draw(int layerNum)
{
	if (layerNum != layerNum_)
		return;

	if (renderTargetNum_ == CameraManager::GetCurrentCameraNum())
	{

		Direct3D::SetDepthBufferWriteEnable(false);
		D2D::GetRenderTarget()->BeginDraw();
		D2D::GetRenderTarget()->DrawTextLayout(transform2D, pLayout_, pColorBrush_);
		//D2D::GetRenderTarget()->DrawText(pText_, textLength_, pTextFormat_,
		//							    { transform2D.x + layoutRect_.left,
		//								  transform2D.y + layoutRect_.top,
		//								  transform2D.x + layoutRect_.right,
		//								  transform2D.y + layoutRect_.bottom }, pColorBrush_);
		D2D::GetRenderTarget()->EndDraw();
		Direct3D::SetDepthBufferWriteEnable(true);
	}
}

void Text::SetColor(const XMFLOAT4& color)
{
	D2D1_COLOR_F colorF = { color.x, color.y,color.z,color.w };
	pColorBrush_->SetColor(colorF);
}
void Text::SetRatio(float ratioX, float ratioY)
{
	//��ʂ̊����ɉ����Ĉړ������Adefaultos_��
	transform2D.x = (CameraManager::GetCamera(renderTargetNum_).GetViewPort().Width * ratioX) + ( float)defaultPos_.x;
	transform2D.y = (CameraManager::GetCamera(renderTargetNum_).GetViewPort().Height * ratioY)+(float)defaultPos_.y;
}

void Text::SetPosition(const XMFLOAT2& position)
{
	transform2D.x = position.x+defaultPos_.x;
	transform2D.y = position.y+defaultPos_.y;
}

void Text::SetTextLayout()
{
}

HRESULT Text::SetText(const std::string& text)
{
	//�e�L�X�g�̏����ݒ���R�s�[���ē��꒼��
	std::filesystem::path str = text;
	std::string locale = setlocale(LC_CTYPE, NULL);
	setlocale(LC_CTYPE, "ja-jp");
	
	HRESULT hr;
	FontData data;
	//�t�H���g��
	hr = pTextFormat_->GetFontFamilyName((WCHAR*)data.fontName_.c_str(), pTextFormat_->GetFontFamilyNameLength() + 1);
	if (FAILED(hr))
		return hr;
	//�t�H���g�T�C�Y
	data.fontSize_ = pTextFormat_->GetFontSize();
	hr = pTextFormat_->GetLocaleName((WCHAR*)data.locale_.c_str(), pTextFormat_->GetLocaleNameLength() + 1);
	if (FAILED(hr))
		return hr;
	//�t�H���g�R���N�V����
	hr = pTextFormat_->GetFontCollection(&data.pCollection_);
	if (FAILED(hr))
		return hr;
	//�e�L�X�g�̈ʒu
	DWRITE_TEXT_ALIGNMENT textAlignment = pTextFormat_->GetTextAlignment();
	DWRITE_PARAGRAPH_ALIGNMENT paraAlignment = pTextFormat_->GetParagraphAlignment();
	
	//�X�g���b�`
	data.fontStretch_ = pTextFormat_->GetFontStretch();
	//�X�^�C��
	data.fontStyle_ = pTextFormat_->GetFontStyle();
	//�E�F�C�g
	data.fontWaight_ = pTextFormat_->GetFontWeight();

	//�����ݒ�
	SAFE_RELEASE(pTextFormat_);
	hr = D2D::GetDWriteFactory()->CreateTextFormat(data.fontName_.c_str(), data.pCollection_, data.fontWaight_, data.fontStyle_, data.fontStretch_, data.fontSize_, data.locale_.c_str(), &pTextFormat_);
	if (FAILED(hr))
		return hr;
	pText_ = str.wstring();
	setlocale(LC_CTYPE, locale.c_str());
	textLength_ = pText_.length();
	SAFE_RELEASE(pLayout_);
	hr=D2D::GetDWriteFactory()->CreateTextLayout(pText_.c_str(), (UINT32)textLength_, pTextFormat_, (layoutRect_.right - layoutRect_.left), (layoutRect_.bottom - layoutRect_.top), &pLayout_);
	if (FAILED(hr))
		return hr;
	pTextFormat_->SetTextAlignment(textAlignment);
	pTextFormat_->SetParagraphAlignment(paraAlignment);
	pLayout_->SetTextAlignment(textAlignment);
	pLayout_->SetParagraphAlignment(paraAlignment);
	return hr;
}

HRESULT Text::SetFontWeight(DWRITE_FONT_WEIGHT weightType, UINT32 startPos, UINT32 length)
{
	DWRITE_TEXT_RANGE range;
	range.length = length;
	range.startPosition = startPos;
	return pLayout_->SetFontWeight(weightType, range);
}

HRESULT Text::SetFontStyle(DWRITE_FONT_STYLE style, const UINT32& startPos, const UINT32& length)
{
	HRESULT hr;
	DWRITE_TEXT_RANGE range;
	range.length = length;
	range.startPosition = startPos;
	return pLayout_->SetFontStyle(style, range);
}




HRESULT Text::SetTextSize(float size, UINT32 startPos, UINT32 length)
{
	HRESULT hr;
	if ((long long)startPos + length >= (UINT)textLength_)
	{
		length = startPos + length - (UINT32)textLength_;
	}
	hr = pLayout_->SetFontSize(size, { startPos,length });
	return hr;
}
HRESULT Text::SetTextSize(float size)
{
	if (size <= 0.0f)
		return E_FAIL;
	HRESULT hr;

	//�t�H���g�f�[�^�쐬
	FontData data;

	data.fontSize_ = size;

	//���̃e�L�X�g�̏����ݒ���R�s�[
	//�t�H���g��
	hr = pTextFormat_->GetFontFamilyName((WCHAR*)data.fontName_.c_str(), pTextFormat_->GetFontFamilyNameLength()+1);
	if (FAILED(hr))
		return hr;
	//���P�[��
	hr = pTextFormat_->GetLocaleName((WCHAR*)data.locale_.c_str(), pTextFormat_->GetLocaleNameLength()+1);
	if (FAILED(hr))
		return hr;
	//�t�H���g�R���N�V����
	hr = pTextFormat_->GetFontCollection(&data.pCollection_);
	if (FAILED(hr))
		return hr;
	//�e�L�X�g�̈ʒu
	DWRITE_TEXT_ALIGNMENT textAlignment = pTextFormat_->GetTextAlignment();
	DWRITE_PARAGRAPH_ALIGNMENT paraAlignment = pTextFormat_->GetParagraphAlignment();
	
	//�X�g���b�`
	data.fontStretch_ = pTextFormat_->GetFontStretch();
	//�X�^�C��
	data.fontStyle_ = pTextFormat_->GetFontStyle();
	//�E�F�C�g
	data.fontWaight_ = pTextFormat_->GetFontWeight();
	
	//�����ݒ�
	SAFE_RELEASE(pTextFormat_);
	hr = D2D::GetDWriteFactory()->CreateTextFormat(data.fontName_.c_str(), data.pCollection_, data.fontWaight_, data.fontStyle_, data.fontStretch_, data.fontSize_, data.locale_.c_str(), &pTextFormat_);
	if (FAILED(hr))
		return hr;
	SAFE_RELEASE(pLayout_);
	hr = D2D::GetDWriteFactory()->CreateTextLayout(pText_.c_str(), (UINT32)textLength_, pTextFormat_, (layoutRect_.right - layoutRect_.left), (layoutRect_.bottom - layoutRect_.top), &pLayout_);
	if (FAILED(hr))
		return hr;
		
	pTextFormat_->SetTextAlignment(textAlignment);
	pTextFormat_->SetParagraphAlignment(paraAlignment);
	pLayout_->SetTextAlignment(textAlignment);
	pLayout_->SetParagraphAlignment(paraAlignment);
	return hr;
}

HRESULT Text::SetFontCollection(IDWriteFontCollection* collection, UINT32 startPos, UINT32 length)
{
	DWRITE_TEXT_RANGE range;
	range.startPosition = startPos;
	range.length = length;
	HRESULT hr = pLayout_->SetFontCollection(collection, range);
	return hr;
}

HRESULT Text::SetFont(const FontData& data)
{
	
	FontData fData;
	fData.fontName_ = data.fontName_;
	fData.pCollection_ = data.pCollection_;
	fData.locale_ = data.locale_;
	fData.fontWaight_ = data.fontWaight_;
	fData.fontStyle_ = data.fontStyle_;
	fData.fontStretch_ = data.fontStretch_;
	HRESULT hr= D2D::GetDWriteFactory()->CreateTextFormat(fData.fontName_.c_str(), fData.pCollection_, data.fontWaight_/*DWRITE_FONT_WEIGHT_REGULAR*/, data.fontStyle_/*DWRITE_FONT_STYLE_NORMAL*/, data.fontStretch_/*DWRITE_FONT_STRETCH_NORMAL*/, data.fontSize_, data.locale_.c_str(), &pTextFormat_);
	assert(hr==S_OK);

	pFontName_ = fData.fontName_;
	return hr;
}
HRESULT Text::SetFont(const std::string& fontName, const UINT32& startPos, const UINT32& length)
{
	DWRITE_TEXT_RANGE range;
	range.startPosition = startPos;
	range.length = length;
	BOOL isFont = false;
	std::filesystem::path name = fontName;
	UINT32 index;
	HRESULT hr;
	//�G���W�����̃t�H���g�R���N�V�����ɖړI�̃t�H���g�����邩�ǂ���
	D2D::GetCollection()->FindFamilyName((wchar_t*)name.wstring().c_str(), &index, &isFont);
	if (isFont == false)
	{
		//���������ꍇ�V�X�e���t�H���g�T��
		D2D::GetSystemFontCollection()->FindFamilyName((wchar_t*)name.wstring().c_str(), &index, &isFont);
		if (isFont)
		{
			//�t�H���g�R���N�V�����ݒ�
			hr = pLayout_->SetFontCollection(D2D::GetSystemFontCollection(), range);
			//�t�H���g�Ƃ��͈̔͐ݒ�
			hr = pLayout_->SetFontFamilyName(name.wstring().c_str(), range);
			pFontName_ = name.wstring();
			return hr;
		}
		//�t�H���g��������Ȃ��ꍇ�Ȃ�����Ȃ�
		else
			return E_FAIL;
	}
	//�t�H���g�R���N�V�����ݒ�
	hr = pLayout_->SetFontCollection(D2D::GetCollection(),range);
	//�t�H���g�Ƃ��͈̔͐ݒ�
	hr = pLayout_->SetFontFamilyName(name.wstring().c_str(), range);
	pFontName_ = name.wstring();
	return hr;
}
void Text::SetTransform(const TEXT_POSITION& pos)
{
	transform2D = pos;
}

void Text::SetRect(const TEXT_RECT& rect)
{	
	layoutRect_ = rect;
}
void Text::SetAlignmentType(const ALIGNMENT_TYPE& type)
{

	switch (type)
	{
	case LEFT_TOP:
		//���_����
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		break;

	case LEFT_CENTER:
		//���_��
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		break;
	
	case LEFT_BOTTOM:
		//���_����
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		break;

	case CENTER_TOP:
		//���_��
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		break;
	
	case CENTER_CENTER:
		//���_����
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		break;
	
	case CENTER_BOTTOM:
		//���_��
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		break;

	case RIGHT_TOP:
		//���_�E��
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		break;
	case RIGHT_CENTER:
		//���_�E
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		break;

	case RIGHT_BOTTOM:
		//���_�E��
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		break;

	default:
		//�f�t�H���g
		pLayout_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pLayout_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		break;
	}
}

