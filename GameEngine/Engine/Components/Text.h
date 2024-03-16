#pragma once
#include"../DirectX_11/Direct2D.h"
//#include"Engine/DirectX_11/Direct3D.h"
#include<string>
typedef D2D_RECT_F TEXT_RECT;//left top right bottom
typedef D2D1_POINT_2F TEXT_POSITION;

	struct FontData
	{
		float fontSize_;
		std::wstring fontName_;		//�t�H���g��
		std::wstring locale_;			//���P�[��
		DWRITE_FONT_WEIGHT	fontWaight_;		//�t�H���g�̑���
		DWRITE_FONT_STYLE   fontStyle_;			//�t�H���g�X�^�C��
		DWRITE_FONT_STRETCH fontStretch_;
		IDWriteFontCollection* pCollection_;	//�t�H���g�R���N�V����
		FontData()
		{
			fontSize_ = 72.0f;
			fontWaight_ = DWRITE_FONT_WEIGHT_REGULAR;
			fontStyle_ = DWRITE_FONT_STYLE_NORMAL;
			fontStretch_ = DWRITE_FONT_STRETCH_NORMAL;
			pCollection_ = nullptr;
		}
	};

class Text
{
private:
	size_t				  textLength_;		//�e�L�X�g�̒���
	D2D1_RECT_F			  layoutRect_;		//���C�A�E�g���N�g
	std::wstring		  pText_;			//�e�L�X�g
	std::wstring		  pFontName_;
	ID2D1SolidColorBrush* pColorBrush_;		//�u���V
	IDWriteTextFormat*	  pTextFormat_;     //�e�L�X�g�t�H�[�}�b�g
	IDWriteTextLayout*	  pLayout_;			//�e�L�X�g���C�A�E�g
	int renderTargetNum_;
	int layerNum_;
	TEXT_POSITION defaultPos_;
public:
	TEXT_POSITION				  transform2D;		//���W
	Text(const int& renderTargetNum=0);
	Text(const std::string& text, const std::string& fontName, const TEXT_RECT& rect, int renderTargetNum = 0 ,int layerNum = 0, const DWRITE_FONT_WEIGHT& wight = DWRITE_FONT_WEIGHT_NORMAL, const DWRITE_FONT_STYLE& style = DWRITE_FONT_STYLE_NORMAL, const DWRITE_FONT_STRETCH& stretch = DWRITE_FONT_STRETCH_NORMAL, const ALIGNMENT_TYPE& type = LEFT_TOP);
	//Text(std::string text);
	~Text();
	/// <summary>
	/// �e�L�X�g�̃��[�h
	/// </summary>
	/// <param name="text">�\�����镶��</param>
	/// <param name="fontName">�t�H���g��</param>
	/// <param name="rect">��`�̃T�C�Y</param>
	/// <param name="type">�A���C�����g�ݒ�</param>
	/// <returns></returns>
	int Load(const std::string& text, const std::string& fontName, const TEXT_RECT& rect, const ALIGNMENT_TYPE& type);
	void Initialize();
	//�`��
	void Draw();
	//�`�惌�C���[����̕`��
	void Draw(int layerNum);
	//�A���C�����g�ݒ�
	void SetAlignmentType(const ALIGNMENT_TYPE& type);
	//�����̐F�ݒ�
	void SetColor(const XMFLOAT4& color);
	//�t�H���g�ݒ�
	HRESULT SetFont(const FontData& data);
	/// <summary>
	/// �t�H���g�ݒ�
	/// </summary>
	/// <param name="fontName">�t�H���g��</param>
	/// <param name="startPos">�t�H���g�ύX�ʒu</param>
	/// <param name="length">�ύX���镶����̒���</param>
	/// <returns></returns>
	HRESULT SetFont(const std::string& fontName, const UINT32& startPos = 0, const UINT32& length=UINT32_MAX);
	/// <summary>
	/// �e�L�X�g�ύX
	/// </summary>
	/// <param name="text">�\�����镶��</param>
	/// <returns></returns>
	HRESULT SetText(const std::string& text);
	/// <summary>
	/// �e�L�X�g�T�C�Y�ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	/// <param name="startPos">�ݒ肷�镶���̈ʒu</param>
	/// <param name="length">�ݒ肷�镶���̒���</param>
	/// <returns></returns>
	HRESULT SetTextSize(float size,UINT32 startPos,UINT32 length);
	/// <summary>
	/// �e�L�X�g�T�C�Y�ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	/// <returns></returns>
	HRESULT SetTextSize(float size);
	/// <summary>
	/// �t�H���g�R���N�V�����ݒ�
	/// </summary>
	/// <param name="collection">�R���N�V����</param>
	/// <param name="startPos">�R���N�V�����𔽉f���镶���̈ʒu</param>
	/// <param name="length">���f���镶���̒���</param>
	/// <returns></returns>
	HRESULT SetFontCollection(IDWriteFontCollection* collection,UINT32 startPos,UINT32 length);
	//�E�F�C�g�ݒ�
	HRESULT SetFontWeight(DWRITE_FONT_WEIGHT weightType,UINT32 startPos,UINT32 length);
	//�X�^�C���ݒ�
	HRESULT SetFontStyle(DWRITE_FONT_STYLE style,const UINT32& startPos,const UINT32& length);
	
	void SetTransform(const TEXT_POSITION& pos);
	void SetTextLayout();
	/// <summary>
	/// ��ʂ̊����ňʒu�ݒ�(0�`1)
	/// ��ʍ��オ���_
	/// </summary>
	/// <param name="ratioX">�������̊���</param>
	/// <param name="ratioY">�c�����̊���</param>
	void SetRatio(float ratioX,float ratioY);
	/// <summary>
	/// �ʒu�ݒ�
	/// </summary>
	/// <param name="position">�ʒu</param>
	void SetPosition(const XMFLOAT2& position);
	/// <summary>
	/// ��`�̃T�C�Y�ݒ�
	/// </summary>
	/// <param name="rect">�T�C�Y</param>
	void SetRect(const TEXT_RECT& rect);
	const TEXT_RECT& GetRect() const { return layoutRect_; }
	/// <summary>
	/// �e�L�X�g�T�C�Y
	/// </summary>
	/// <returns>�T�C�Y</returns>
	int GetTextSize() const;
	void Release();

};

