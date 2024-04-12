#pragma once
#include"../DirectX_11/Sprite.h"
#include<memory>

class GameObject;
class Image
{
private:
	GameObject* attachObject_;
	std::string imageName_;
	std::shared_ptr<Sprite> pSprite_;
	RECT rect_;
	XMFLOAT4 color_;
	float alpha_;
	XMFLOAT2 scroll_;
	int drawTargetNumber_;
	int layerNum_;
	Transform transform_;
	bool isStatic_;
	bool isDraw_;
public:
	Image(int cameraNum = -1, int layerNum = 0);
	Image(GameObject* object,int cameraNum = -1,int layerNum=0);
	~Image();
	//画像ロード
	bool Load(const std::string& name, const std::string& tab = "");
	bool StaticLoad(const std::string& name);
	//座標設定
	void SetPosition(const XMFLOAT3& pos);
	//座標設定(ピクセル単位)
	void SetPositionAtPixel(const XMFLOAT3& pos);
	void AddPositionAtPixel(const XMFLOAT3& deltaPos);
	//描画するかどうか
	void SetDraw(bool isDraw) { isDraw_ = isDraw; }
	//描画してるかどうか
	bool IsDraw() { return isDraw_; }
	//透明度設定
	void SetAlpha(float alpha);
	//色設定
	void SetColor(const float color) noexcept;
	void SetColor(const XMFLOAT3& color) noexcept;
	void SetColor(const XMFLOAT4& color) noexcept;
	//画像のスクロール量設定
	void SetScroll(const XMFLOAT2& scroll);
	//画像サイズ設定
	void SetSize(const XMFLOAT3& size);
	XMFLOAT3 GetSize()				{ return transform_.scale_;}
	XMFLOAT3 GetSizeAtPixel()
	{
		XMFLOAT3 size = pSprite_->GetSize();
		return { size.x * transform_.scale_.x,size.y * transform_.scale_.y,0 };
	}
	XMFLOAT3 GetOriginalImageSize() { return pSprite_->GetSize();}
	//画像回転
	void SetRotation(const XMFLOAT3& rotate);
	//描画対象設定(複数画面時)
	void SetDrawTarget(int targetNum) { drawTargetNumber_ = targetNum; }
	XMFLOAT3 ConvertToRatio(XMFLOAT3 pos);
	XMFLOAT3 ConvertToPixel(XMFLOAT3 pos);
	XMFLOAT3 ConvertToPixel(XMVECTOR pos);
	XMFLOAT3 GetPositionAtPixel();
	XMFLOAT3 GetRatio();
	XMFLOAT3 GetPosition() const { XMFLOAT3 pos; XMStoreFloat3(&pos, transform_.position_); return pos; }
	//描画
	void Draw();
	void Draw(int layerNum);
	void SimpleDraw();

	//レイヤー番号のセッター
	void SetLayer(int layer);


	bool IsHitCursor();
	GameObject* GetAttachedObject() const { return attachObject_; }
};

