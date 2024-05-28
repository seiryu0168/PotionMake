#pragma once
#include"Engine/GameObject/GameObject.h"

/// <summary>
/// ウィンドウが必要なUIオブジェクトの基底クラス
/// </summary>
class Window_Base : public GameObject
{
	int titleImageNum_[3];
public:
	XMFLOAT3 uiPos_;
	XMFLOAT3 titlePos_;
	Window_Base(Object* parent,const std::string& name);
	~Window_Base() {};
	
	//const XMFLOAT3& GetUIPosition() { return uiPos_; }
	//const XMFLOAT3& GetTilePosition() { return titlePos_; }
	//void SetUIPosition(const XMFLOAT3& pos) { uiPos_ = pos; }
	//void SetTitlePosition(const XMFLOAT3& pos) { titlePos_ = pos; }
	/// <summary>
	/// ウィンドウの枠を作る関数
	/// </summary>
	/// <param name="backImage">背景の画像</param>
	/// <param name="uiPos">ウィンドウを配置する位置</param>
	/// <param name="windowSize">ウィンドウのサイズ。基準は1024x1024</param>
	/// <param name="edgeSize">枠の太さ</param>
	void CreateBase(const std::string& backImage = "Assets/Image/UIBaseImage2.png", const XMFLOAT3& uiPos = { 0,0,0 }, XMFLOAT2 windowSize = {0,0}, float edgeSize=0.3f, int layer = 0);
	void CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str,float textSize,const XMINT3& color,int layer = 0);
	void ChangeTitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str, float textSize, const XMINT3& color, int layer = 0);
	
};

