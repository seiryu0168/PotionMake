#pragma once
#include<unordered_map>
#include<memory>
#include<bitset>
#include"ECS.h"
#include"System.h"

class SystemManager
{
private:
	//�V�X�e���^�̕�����|�C���^����V�O�l�`���ւ̃}�b�v
	std::unordered_map<const char*, Signature> signatures_{};
	//�V�X�e���^�̕�����|�C���^����V�X�e���|�C���^�ւ̃}�b�v
	std::unordered_map<const char*, std::shared_ptr<System>> systems_{};

public:
	void EntityDestroyed(Entity entity);
	void EntitySignatureChanged(Entity entity, const Signature entitySignature);
	void AllSystemUpdate();
	void Clear();

	/// <summary>
	/// �V�X�e���N���X�̓o�^
	/// �V�X�e���N���X�̓G���W���̏��������ɂ��ׂēo�^����A
	/// �Q�[�����I��鎞�ɂ��ׂď��������
	/// </summary>
	/// <typeparam name="T">�V�X�e���̃N���X</typeparam>
	/// <returns>�V�X�e���N���X�̃X�}�[�g�|�C���^</returns>
	template <typename T>
	std::shared_ptr<T> RegisterSistem()
	{
		const char* typeName = typeid(T).name();
		//�V�X�e�������܂Œǉ������̂Ɠ������̂�����ꍇ�x��
		assert(systems_.find(typeName) == systems_.end() && "Registering system more than once");
		//�V�X�e���̃|�C���^���쐬���A�O���Ŏg�����߂ɕԂ�
		auto system = std::make_shared<T>();
		systems_.insert({ typeName,system });
		return system;
	}
	/// <summary>
	/// �V�O�l�`�����Z�b�g
	/// </summary>
	/// <typeparam name="T">�R�Â���V�X�e���N���X</typeparam>
	/// <param name="signature">�V�O�l�`��</param>
	template <typename T>
	void SetSignature(const Signature& signature)
	{
		const char* typeName = typeid(T).name();
		assert(signatures_.find(typeName) == signatures_.end() && "System used before registered");
		//�V�X�e���ɃV�O�l�`�����Z�b�g
		signatures_.insert({ typeName,signature });
	}
	/// <summary>
	/// �V�X�e���N���X�̎擾
	/// </summary>
	/// <typeparam name="T">�~�����V�X�e���N���X</typeparam>
	/// <returns>�V�X�e���N���X</returns>
	template <typename T>
	System* GetSystem() const
	{
		const char* typeName = typeid(T).name();
		if (signatures_.find(typeName) == signatures_.end())
			return nullptr;
		return systems_.find(typeName)->second.get();
	}
};

