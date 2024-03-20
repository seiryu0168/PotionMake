#pragma once
#include"../ECS/System.h"
#include"../Coordinator.h"
#include"../Components/Collider.h"
class ColliderSystem : public System
{
private:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	struct CONSTANT_BUFFER
	{
		XMMATRIX matWorld;
		XMMATRIX matUVTrans;
		XMFLOAT4 color;
		XMFLOAT4 ChangeColor;
	};
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

};

