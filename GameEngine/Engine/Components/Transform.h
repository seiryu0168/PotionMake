#pragma once
#include"../DirectX_11/Math.h"
#include<memory>
#include<List>
using namespace DirectX;
class Object;
class Transform
{
	Object* attachObject_;
	bool isDead_;
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;	//�g��s��
	XMVECTOR front_;
	XMVECTOR right_;
	XMVECTOR left_;
	XMVECTOR back_;
public:

	XMVECTOR position_;	//�ʒu
	XMVECTOR rotate_;	//����
	XMFLOAT3 scale_;	//�g�嗦

	XMVECTOR baseVec_;	//��ƂȂ�x�N�g��

	Transform* pParent_;//�e�̏��
	std::list<Transform*> childList_;

	//�R���X�g���N�^
	//Transform();
	Transform(Object* obj = nullptr,Transform* parent = nullptr);

	//�f�X�g���N�^
	~Transform();

	void PushBackChild(Transform* child);

	//�e�s��̌v�Z
	void Calclation();

	//�X�V
	void Update();

	void UpdateSub();
	//��]
	void RotateAxis(const XMVECTOR& axis, float angle);
	void RotateEular(const XMFLOAT3& rotation);
	void RotateEular(float x,float y,float z);

	Object* GetAttachedObject() const { return attachObject_; }

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

	XMVECTOR GetFront() { return front_; }
	XMVECTOR GetRight() { return right_; }
	XMVECTOR GetLeft() { return left_; }
	XMVECTOR GetBack() { return back_; }

	static XMFLOAT3 Float3Add(const XMVECTOR& add1, const XMVECTOR& add2)
	{
		return StoreFloat3(add1 + add2);
	}
	void Dead() { isDead_ = true;}
	bool IsDead() { return isDead_; }
	void RemoveChild();
};

