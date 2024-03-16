#pragma once
#include<unordered_map>
#include<memory>
#include"ComponentArray.h"
#include"ECS.h"

class ComponentManager
{
private:
	//������^�|�C���^����R���|�[�l���g�^�ւ̃}�b�s���O
	std::unordered_map<const char*, ComponentType> componentTypes_{};
	//������^�|�C���^����R���|�[�l���g�z��ւ̃}�b�s���O
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays_{};
	//���ɓo�^����R���|�[�l���g�̃^�C�v
	ComponentType nextComponentType_{};
	//�R���|�[�l���g�z��̎擾
	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray() const
	{
		//�R���|�[�l���g
		const char* typeName = typeid(T).name();
		assert(componentTypes_.find(typeName) != componentTypes_.end()&&"Component not registered before use");
		return std::static_pointer_cast<ComponentArray<T>>(componentArrays_.at(typeName));
	}

public:
	//�R���|�[�l���g�̓o�^
	template <typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();
		//�����R���|�[�l���g�^�C�v������ꍇ�A�o�^���Ȃ�
		if (componentTypes_.find(typeName) != componentTypes_.end())
			return;
		assert(componentTypes_.find(typeName) == componentTypes_.end() && "Registaring component type more once");
		componentTypes_.insert({ typeName,nextComponentType_ });
		componentArrays_.insert({ typeName, std::make_shared<ComponentArray<T>>()});
		++nextComponentType_;
	}
	/// <summary>
	/// �R���|�[�l���g�^�C�v�̎擾
	/// </summary>
	/// <typeparam name="T">�R���|�[�l���g�^�C�v</typeparam>
	/// <returns>�R���|�[�l���g�^�C�v�̔ԍ�(unsigned int)</returns>
	template <typename T>
	ComponentType GetComponentType() const
	{
		const char* typeName = typeid(T).name();
		assert(componentTypes_.find(typeName) != componentTypes_.end() && "Component not registered before use");
		return componentTypes_.at(typeName);
	
	}
	/// <summary>
	/// �R���|�[�l���g�̒ǉ�
	/// �G���e�B�e�B�ƕR�Â����ăR���|�[�l���g���ǉ������
	/// </summary>
	/// <typeparam name="T">�R���|�[�l���g�^�C�v</typeparam>
	/// <param name="entity">�ǉ�����G���e�B�e�B</param>
	/// <param name="component">�ǉ�����R���|�[�l���g</param>
	template <typename T>
	void AddComponent(const Entity& entity, const T& component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}
	/// <summary>
	/// �R���|�[�l���g�폜
	/// </summary>
	/// <typeparam name="T">�R���|�[�l���g�^�C�v</typeparam>
	/// <param name="entity">��������R���|�[�l���g�ɕR�Â���ꂽ�G���e�B�e�B</param>
	template <typename T>
	void RemoveComponent(const Entity& entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}
	//�R���|�[�l���g�S������
	void AllRemoveComponent();
	/// <summary>
	/// �R���|�[�l���g�擾
	/// </summary>
	/// <typeparam name="T">�R���|�[�l���g�^�C�v</typeparam>
	/// <param name="entity">�~�����R���|�[�l���g�ɕR�Â���ꂽ�G���e�B�e�B</param>
	/// <returns>�R���|�[�l���g</returns>
	template <typename T>
	T& GetComponent(const Entity& entity) const
	{
		return GetComponentArray<T>()->GetData(entity);
	}
	/// <summary>
	/// �G���e�B�e�B�𖳌���
	/// </summary>
	/// <param name="entity">�������������G���e�B�e�B</param>
	void EntityDestroyed(const Entity& entity)
	{
		for (auto const& pair : componentArrays_)
		{
			auto const& component = pair.second;
			component->EntityDestroyed(entity);
		}
	}
};

