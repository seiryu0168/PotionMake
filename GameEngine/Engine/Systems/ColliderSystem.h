#pragma once
#include"../ECS/System.h"
#include"../Coordinator.h"
#include"../Components/Collider.h"
class ColliderSystem : public System
{
public:
	ColliderSystem();
	~ColliderSystem() {};
	void Update() override;
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

