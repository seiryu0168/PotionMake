#pragma once
#include"../ECS/System.h"
#include"../Coordinator.h"
#include"../Components/Collider.h"
class ColliderSystem : public System
{
private:
	ID3D11Buffer* pBoxVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pBoxIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pBoxConstantBuffer_;	//�R���X�^���g�o�b�t�@

	ID3D11Buffer* pSphereVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pSphereIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pSphereConstantBuffer_;	//�R���X�^���g�o�b�t�@

	struct CONSTANT_BUFFER
	{
		XMMATRIX matWVP;			//���[���h�A�r���[�A�v���W�F�N�V�����s��̍���(���_�ϊ��Ɏg��)
		XMMATRIX matW;				//���[���h�s��
		XMMATRIX matNormal;			//��]�s��Ɗg��s��̍���(�@���̕ό`�Ɏg��)
	};

	const struct VERTEX
	{
		XMVECTOR position;
		//XMVECTOR uv
	};

	VERTEX boxVertices_[8] = 
	  { {XMVectorSet(-1,1,-1,0)},
		{XMVectorSet(1,1,-1,0)},
		{XMVectorSet(1,-1,-1,0)},
		{XMVectorSet(-1,-1,-1,0)},
		{XMVectorSet(-1,1,1,0)},
		{XMVectorSet(1,1,1,0)},
		{XMVectorSet(1,-1,1,0)},
		{XMVectorSet(-1,-1,1,0)}
	  };

	VERTEX sphereVertices_[36];
	//CONSTANT_BUFFER boxCb;
	//CONSTANT_BUFFER sphereCb;

	int boxIndex[36] = { 0,1,3, 0,1,2, 1,6,2, 1,5,6, 5,7,6, 5,4,7, 4,3,7, 4,0,3, 0,4,5, 0,5,1, 2,7,3, 2,6,7 };

	void CreateVB();
	void CreateIB();
	void CreateCB();
public:
	ColliderSystem();
	~ColliderSystem() {};
	void Update() override;
	void Draw(int drawLayer = 0) override;
	void Release() override;
	void CheckRemove() override;
	/// <summary>
	/// �ǂ�Ƃǂꂪ�������Ă邩�`�F�b�N
	/// </summary>
	/// <param name="firstTarget">�`�F�b�N�����R���C�_�[</param>
	/// <param name="secondTarget">�`�F�b�N����R���C�_�[</param>
	void CheckCollision(Collider* firstTarget, Collider* secondTarget) const;
	//�{�b�N�X���m�̓����蔻��
	bool IsHitBox_Box(Collider* firstTarget, Collider* secondTarget) const;
	//�{�b�N�X�Ƌ��̓����蔻��
	bool IsHitBox_Sphere(Collider* firstTarget, Collider* secondTarget) const;
	//���Ƌ��̓����蔻��	
	bool IsHitSphere_Sphere(Collider* firstTarget, Collider* secondTarget) const;
	//OBB�R���C�_�[���m�̓����蔻��
	bool IsHitOBB_OBB(Collider* firstTarget, Collider* secondTarget) const;

};

