#pragma once
#include "../DirectX_11/Direct3D.h"
#include <DirectXMath.h>
class Camera
{
	XMVECTOR position_;			//�J�����̈ʒu�i���_�j
	XMVECTOR target_;			//����ʒu�i�œ_�j
	XMVECTOR upVector_;			//��x�N�g��
	XMMATRIX viewMatrix_;		//�r���[�s��
	XMMATRIX projMatrix_;		//�v���W�F�N�V�����s��
	XMMATRIX billBoardMatrix_;	//�r���{�[�h�s��
	float	 angleOfView_;		//����p
	float	 aspectRadio_;		//�A�X�y�N�g��
	float	 nearClipping_;		//�j�A�N���b�s���O
	float	 farClipping_;		//�t�@�[�N���b�s���O
	D3D11_VIEWPORT viewPort_;	//�r���[�|�[�g
public:
	Camera();
	void Initialize(float width, float height, float nearClipping, float farClipping);
	void Update();
	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target);

	//�J�����̏�����x�N�g����ݒ�
	void SetUpVector(XMVECTOR upVector);

	/// <summary>
	/// �v���W�F�N�V�����s���ݒ�
	/// </summary>
	/// <param name="aov">��p</param>
	/// <param name="aspectRadio">�A�X�y�N�g��</param>
	/// <param name="nearZ">�j�A�N���b�s���O</param>
	/// <param name="farZ">�t�@�[�N���b�s���O</param>
	void SetProjection(float aov, float aspectRadio, float nearZ, float farZ);

	/// <summary>
	/// ��p�ݒ�
	/// </summary>
	/// <param name="aov">��p</param>
	void SetAOV(float aov);

	/// <summary>
	/// �A�X�y�N�g��ݒ�
	/// </summary>
	/// <param name="aspect">�A�X�y�N�g��</param>
	void SetAspectRadio(float aspect);

	/// <summary>
	/// �N���b�s���O�͈͐ݒ�
	/// </summary>
	/// <param name="nearZ">�j�A�N���b�s���O</param>
	/// <param name="farZ">�t�@�[�N���b�s���O</param>
	void SetClipping(float nearZ, float farZ);

	void SetViewPort(float width, float height, float minDepth, float maxDepth, float topLeftX, float topLeftY);

	//���_(������ʒu)���擾
	XMFLOAT3 GetPosition();

	//�œ_�擾
	XMVECTOR GetTarget() { return target_; }

	//�r���[�s����擾
	XMMATRIX GetViewMatrix() { return viewMatrix_; }

	//�r���{�[�h�p��]�s��
	XMMATRIX GetBillBoardMatrix() { return billBoardMatrix_; }

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix() { return projMatrix_; }

	D3D11_VIEWPORT GetViewPort() { return viewPort_; }

};

