#pragma once
#include"SnowCone_ToppingMenu.h"

class SnowCone_ToppingSelect : public SnowCone_ToppingMenu
{
private:
	int selectFrame_;
	int toppingText_;
public:
	SnowCone_ToppingSelect(Object* parent);
	~SnowCone_ToppingSelect();

	void Initialize() override;
	void Update() override;
	/// <summary>
	/// ����
	/// </summary>
	void Input();
	/// <summary>
	///	�J�[�\�����ړ�
	/// </summary>
	void Move();
	/// <summary>
	/// ���I��ł���g�b�s���O�̔ԍ����擾
	/// </summary>
	/// <returns>�g�b�s���O�̔ԍ�</returns>
	int GetToppingNum() { return selectNum_; }
	/// <summary>
	/// UI�̃��Z�b�g
	/// </summary>
	void UIReset();
	void Release() override;
};

