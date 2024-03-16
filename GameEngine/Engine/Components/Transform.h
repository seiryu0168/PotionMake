#pragma once
#include"../DirectX_11/Math.h"
#include<memory>
using namespace DirectX;
class Transform
{
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;	//�g��s��
public:

	XMVECTOR position_;	//�ʒu
	XMVECTOR rotate_;	//����
	XMFLOAT3 scale_;	//�g�嗦

	XMVECTOR baseVec_;	//��ƂȂ�x�N�g��

	Transform* pParent_;//�e�̏��

	//�R���X�g���N�^
	//Transform();
	Transform(Transform* parent = nullptr);

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	void Calclation();
	//��]
	void RotateAxis(const XMVECTOR& axis, float angle);
	void RotateEular(const XMFLOAT3& rotation);

	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();
	//��]�s��Ɗg�k�̋t�s��̌v�Z
	XMMATRIX GetNormalMatrix() const;
	
	//���[���h�s����擾
	XMMATRIX GetWorldMatrix();
	//�e���[�J���s��̎擾
	XMMATRIX GetLocalMatrix() const;
	XMMATRIX GetLocalTranslateMatrix() const;
	XMMATRIX GetLocalRotateMatrix() const;
	XMMATRIX GetLocalScaleMatrix() const;

	//�e���[���h�s��̎擾
	XMMATRIX GetWorldTranslateMatrix();
	XMMATRIX GetWorldRotateMatrix();
	XMMATRIX GetWorldScaleMatrix();

	const XMVECTOR& GetWorldFrontVector();
	const XMVECTOR& GetLocalFrontVector();


	static XMFLOAT3 Float3Add(const XMVECTOR& add1, const XMVECTOR& add2)
	{
		return StoreFloat3(add1 + add2);
	}

	
};

