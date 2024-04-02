#pragma once
#include"../DirectX_11/Direct2D.h"
//#include"Engine/DirectX_11/Direct3D.h"
#include<string>
typedef D2D_RECT_F TEXT_RECT;//left top right bottom
typedef D2D1_POINT_2F TEXT_POSITION;
class GameObject;

	struct FontData
	{
		float fontSize_;
		std::wstring fontName_;		//フォント名
		std::wstring locale_;			//ロケール
		DWRITE_FONT_WEIGHT	fontWaight_;		//フォントの太さ
		DWRITE_FONT_STYLE   fontStyle_;			//フォントスタイル
		DWRITE_FONT_STRETCH fontStretch_;
		IDWriteFontCollection* pCollection_;	//フォントコレクション
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
	GameObject* attachObject_;
	size_t				  textLength_;		//テキストの長さ
	D2D1_RECT_F			  layoutRect_;		//レイアウトレクト
	std::wstring		  pText_;			//テキスト
	std::wstring		  pFontName_;
	ID2D1SolidColorBrush* pColorBrush_;		//ブラシ
	IDWriteTextFormat*	  pTextFormat_;     //テキストフォーマット
	IDWriteTextLayout*	  pLayout_;			//テキストレイアウト
	int renderTargetNum_;
	int layerNum_;
	TEXT_POSITION defaultPos_;
public:
	bool isDraw_;
	TEXT_POSITION				  transform2D;		//座標
	Text(GameObject* object);
	Text(const int& renderTargetNum=0);
	Text(const std::string& text, const std::string& fontName, const TEXT_RECT& rect, int renderTargetNum = 0 ,int layerNum = 0, const DWRITE_FONT_WEIGHT& wight = DWRITE_FONT_WEIGHT_NORMAL, const DWRITE_FONT_STYLE& style = DWRITE_FONT_STYLE_NORMAL, const DWRITE_FONT_STRETCH& stretch = DWRITE_FONT_STRETCH_NORMAL, const ALIGNMENT_TYPE& type = LEFT_TOP);
	//Text(std::string text);
	~Text();
	/// <summary>
	/// テキストのロード
	/// </summary>
	/// <param name="text">表示する文字</param>
	/// <param name="fontName">フォント名</param>
	/// <param name="rect">矩形のサイズ</param>
	/// <param name="type">アライメント設定</param>
	/// <returns></returns>
	int Load(const std::string& text, const std::string& fontName, const TEXT_RECT& rect, const ALIGNMENT_TYPE& type);
	void Initialize();
	//描画
	void Draw();
	//描画レイヤーありの描画
	void Draw(int layerNum);
	//アライメント設定
	void SetAlignmentType(const ALIGNMENT_TYPE& type);
	//文字の色設定
	void SetColor(const XMFLOAT4& color);
	//フォント設定
	HRESULT SetFont(const FontData& data);
	/// <summary>
	/// フォント設定
	/// </summary>
	/// <param name="fontName">フォント名</param>
	/// <param name="startPos">フォント変更位置</param>
	/// <param name="length">変更する文字列の長さ</param>
	/// <returns></returns>
	HRESULT SetFont(const std::string& fontName, const UINT32& startPos = 0, const UINT32& length=UINT32_MAX);
	/// <summary>
	/// テキスト変更
	/// </summary>
	/// <param name="text">表示する文字</param>
	/// <returns></returns>
	HRESULT SetText(const std::string& text);
	/// <summary>
	/// テキストサイズ設定
	/// </summary>
	/// <param name="size">サイズ</param>
	/// <param name="startPos">設定する文字の位置</param>
	/// <param name="length">設定する文字の長さ</param>
	/// <returns></returns>
	HRESULT SetTextSize(float size,UINT32 startPos,UINT32 length);
	/// <summary>
	/// テキストサイズ設定
	/// </summary>
	/// <param name="size">サイズ</param>
	/// <returns></returns>
	HRESULT SetTextSize(float size);
	/// <summary>
	/// フォントコレクション設定
	/// </summary>
	/// <param name="collection">コレクション</param>
	/// <param name="startPos">コレクションを反映する文字の位置</param>
	/// <param name="length">反映する文字の長さ</param>
	/// <returns></returns>
	HRESULT SetFontCollection(IDWriteFontCollection* collection,UINT32 startPos,UINT32 length);
	//ウェイト設定
	HRESULT SetFontWeight(DWRITE_FONT_WEIGHT weightType,UINT32 startPos,UINT32 length);
	//スタイル設定
	HRESULT SetFontStyle(DWRITE_FONT_STYLE style,const UINT32& startPos,const UINT32& length);
	
	void SetTransform(const TEXT_POSITION& pos);
	void SetTextLayout();
	/// <summary>
	/// 画面の割合で位置設定(0～1)
	/// 画面左上が原点
	/// </summary>
	/// <param name="ratioX">横方向の割合</param>
	/// <param name="ratioY">縦方向の割合</param>
	void SetRatio(float ratioX,float ratioY);
	/// <summary>
	/// 位置設定
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const XMFLOAT2& position);
	/// <summary>
	/// 矩形のサイズ設定
	/// </summary>
	/// <param name="rect">サイズ</param>
	void SetRect(const TEXT_RECT& rect);
	const TEXT_RECT& GetRect() const { return layoutRect_; }
	/// <summary>
	/// テキストサイズ
	/// </summary>
	/// <returns>サイズ</returns>
	int GetTextSize() const;
	GameObject* GetAttachedObject() const { return attachObject_; }
	void Release();

};

