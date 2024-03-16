#pragma once
#include"../Engine/GameObject/GameObject.h"

class SnowCone_SyrupSelect;
class SnowCone_ToppingSelect;
class Image;
enum class SELECT_MODE
{
	MODE_SYRUP = 0,
	MODE_TOPPING,
	MODE_COMPLETE,
};
class SnowCone_ToppingUI : public GameObject
{
private:
	SnowCone_SyrupSelect* syrupSelect_;
	SnowCone_ToppingSelect* toppingSelect_;
	SELECT_MODE mode_;
public:
	SnowCone_ToppingUI(Object* parent);
	~SnowCone_ToppingUI();

	void Initialize() override;
	void Update() override;
	/// <summary>
	/// �V���b�v�̔ԍ��擾
	/// </summary>
	/// <returns>�V���b�v�̔ԍ�</returns>
	int GetSyrupData();
	/// <summary>
	/// �g�b�s���O�̔ԍ��擾
	/// </summary>
	/// <returns>�g�b�s���O�̔ԍ�</returns>
	int GetToppingData();
	/// <summary>
	/// ���I�΂�Ă���V���b�v�̉摜���擾����
	/// </summary>
	/// <returns>�摜</returns>
	Image GetCurrentSyrupImage();
	/// <summary>
	/// ���I�΂�Ă���g�b�s���O�̉摜���擾����
	/// </summary>
	/// <returns>�摜</returns>
	Image GetCurrentToppingImage();
	/// <summary>
	/// �V���b�v��I�Ԃ��g�b�s���O��I�Ԃ��̃��[�h��؂�ւ���
	/// </summary>
	/// <param name="mode">���[�h</param>
	void ModeChange(SELECT_MODE mode);
	/// <summary>
	/// UI�����Z�b�g
	/// </summary>
	void ResetUI();
	void Release() override;
};

