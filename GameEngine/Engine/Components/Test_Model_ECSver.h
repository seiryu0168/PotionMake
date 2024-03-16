#pragma once
#include"../DirectX_11/Material.h"
#include<vector>
#include"../Coordinator.h"
#include"../DirectX_11/Fbx.h"
#include"../GameObject/GameObject.h"

//���b�V���N���X�ƃ}�e���A���N���X���R���|�[�l���g�Ƃ��Ēu��
//���f���N���X�ŕ`��
class Test_Model_ECSver// : public Draw3DComponent
{
private:
	bool isDraw_;
	SHADER_TYPE type_;
	int animationFrame_;
	std::shared_ptr<Fbx> fbx_;
	std::vector<Entity> materialList_;
	Entity meshEntity_;
	GameObject* attachObject_;

	int layerNum_;
public:
	Test_Model_ECSver();
	Test_Model_ECSver(GameObject* object, int layerNum = 0);

	//���f���̃��[�h
	bool Load(const std::string& fileName);

	//���C�L���X�g(������)
	void RayCast(RayCastData& rayData);

	//�V�F�[�_�[�^�C�v�ݒ�
	void SetShaderType(SHADER_TYPE type) { type_ = type; }

	/// <summary>
	/// �{�[���̈ʒu�擾
	/// </summary>
	/// <param name="boneName">�{�[����</param>
	/// <returns>�{�[���ʒu</returns>
	const XMVECTOR GetBone(const std::string& boneName);
	/// <summary>
	/// �{�[���̈ʒu�擾
	/// </summary>
	/// <param name="partsNum">�p�[�c�ԍ�</param>
	/// <param name="num">�{�[���̔ԍ�</param>
	/// <returns>�{�[���ʒu</returns>
	const XMVECTOR GetBone(const UINT& partsNum,const UINT& num);
	/// <summary>
	/// �{�[�����擾
	/// </summary>
	/// <param name="partsNum">�p�[�c�ԍ�</param>
	/// <param name="num">�{�[���̔ԍ�</param>
	/// <returns>�{�[����</returns>
	const std::string GetBoneName(const UINT& partsNum, const UINT& num);
	/// <summary>
	/// �{�[���ԍ��擾
	/// </summary>
	/// <returns>�{�[���ԍ�</returns>
	const UINT GetBoneCount();
	//�`�悷�邩�ǂ���
	const bool IsDraw() { return isDraw_; }
	//�`��t���O�̐ݒ�
	void SetDraw(bool isDraw) { isDraw_ = isDraw; }
	/// <summary>
	/// ���f���̐F��ς���
	/// </summary>
	/// <param name="partsNum">�p�[�c�ԍ�</param>
	/// <param name="materialNum">�}�e���A���ԍ�</param>
	/// <param name="color">�F</param>
	void SetCustomColor(int partsNum,int materialNum,const XMFLOAT4& color);
	//�A�^�b�`����Ă���I�u�W�F�N�g��Ԃ�
	GameObject* GetAttachedObject() { return attachObject_; }
	//�`��
	void Draw();
	//�`�惌�C���[����̕`��
	void Draw(int layerNum);

};

