#pragma once
#include"../DirectX_11/Sprite.h"
#include<memory>
class Image
{
private:
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
	Image(int cameraNum = -1,int layerNum=0);
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
	//�摜�̃X�N���[���ʐݒ�
	void SetScroll(const XMFLOAT2& scroll);
	//�摜�T�C�Y�ݒ�
	void SetSize(const XMFLOAT3& size);
	//�摜��]
	void SetRotation(const XMFLOAT3& rotate);
	//�`��Ώېݒ�(������ʎ�)
	void SetDrawTarget(int targetNum) { drawTargetNumber_ = targetNum; }
	XMFLOAT3 ConvertToRatio(XMFLOAT3 pos);
	XMFLOAT3 ConvertToPixel(XMFLOAT3 pos);
	XMFLOAT3 ConvertToPixel(XMVECTOR pos);
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRatio();
	//�`��
	void Draw();
	void Draw(int layerNum);
	void SimpleDraw();

	//���C���[�ԍ��̃Z�b�^�[
	void SetLayer(int layer);

	XMFLOAT3 GetPosition() const { XMFLOAT3 pos; XMStoreFloat3(&pos, transform_.position_); return pos; }

	bool IsHitCursor();
};

