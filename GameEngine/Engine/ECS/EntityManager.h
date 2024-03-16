#pragma once
#include<bitset>
#include<queue>
#include<array>
#include"ECS.h"
//using Entity = unsigned int;
//const Entity MAX_ENTITIES = 5000;
//using ComponentType = unsigned int;
//const ComponentType MAX_COMPONENTS = 32;
//using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
private:
	//�g�p�\�ȃG���e�B�e�B�̃L���[
	std::queue<Entity> availableEntites_{};
	//�G���e�B�e�B�ŊǗ������V�O�l�`���̔z��
	std::array<Signature, MAX_ENTITIES> signatures_{};
	//���g�p���Ă�G���e�B�e�B�̐�
	unsigned int livingEntityCount_{};
public:
	EntityManager();
	~EntityManager();

	//�G���e�B�e�B�̗L����
	Entity CreateEntity();
	//�G���e�B�e�B�𖳌���
	void DestroyEntity(const Entity& entity);
	/// <summary>
	/// �V�O�l�`�����Z�b�g
	/// </summary>
	/// <param name="entity">�V�O�l�`�����Z�b�g����z��̃C���f�b�N�X</param>
	/// <param name="signature">�Z�b�g����V�O�l�`��</param>
	void SetSignature(const Entity& entity, const Signature& signature);
	/// <summary>
	/// �V�O�l�`���̎擾
	/// </summary>
	/// <param name="entity">�~�����V�O�l�`���̃C���f�b�N�X</param>
	/// <returns>�V�O�l�`��</returns>
	Signature GetSignature (const Entity& entity) const;
	//������
	void Initialize();

};

