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
	//�摜���[�h
	bool Load(const std::string& name, const std::string& tab = "");
	bool StaticLoad(const std::string& name);
	//���W�ݒ�
	void SetPosition(const XMFLOAT3& pos);
	//���W�ݒ�(�s�N�Z���P��)
	void SetPositionAtPixel(const XMFLOAT3& pos);
	void AddPositionAtPixel(const XMFLOAT3& deltaPos);
	//�`�悷�邩�ǂ���
	void SetDraw(bool isDraw) { isDraw_ = isDraw; }
	//�`�悵�Ă邩�ǂ���
	bool IsDraw() { return isDraw_; }
	//�����x�ݒ�
	void SetAlpha(float alpha);
	//�F�ݒ�
	void SetColor(const float color) noexcept;
	void SetColor(const XMFLOAT3& color) noexcept;
	void SetColor(const XMFLOAT4& color) noexcept;
	//�摜�̃X�N���[���ʐݒ�
	void SetScroll(const XMFLOAT2& scroll);
	//�摜�T�C�Y�ݒ�
	void SetSize(const XMFLOAT3& size);
	XMFLOAT3 GetSize()				{ return transform_.scale_;}
	XMFLOAT3 GetSizeAtPixel()
	{
		XMFLOAT3 size = pSprite_->GetSize();
		return { size.x * transform_.scale_.x,size.y * transform_.scale_.y,0 };
	}
	XMFLOAT3 GetOriginalImageSize() { return pSprite_->GetSize();}
	//�摜��]
	void SetRotation(const XMFLOAT3& rotate);
	//�`��Ώېݒ�(������ʎ�)
	void SetDrawTarget(int targetNum) { drawTargetNumber_ = targetNum; }
	XMFLOAT3 ConvertToRatio(XMFLOAT3 pos);
	XMFLOAT3 ConvertToPixel(XMFLOAT3 pos);
	XMFLOAT3 ConvertToPixel(XMVECTOR pos);
	XMFLOAT3 GetPositionAtPixel();
	XMFLOAT3 GetRatio();
	XMFLOAT3 GetPosition() const { XMFLOAT3 pos; XMStoreFloat3(&pos, transform_.position_); return pos; }
	//�`��
	void Draw();
	void Draw(int layerNum);
	void SimpleDraw();

	//���C���[�ԍ��̃Z�b�^�[
	void SetLayer(int layer);


	bool IsHitCursor();
	GameObject* GetAttachedObject() const { return attachObject_; }
};

