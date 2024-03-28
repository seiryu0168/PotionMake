#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// �o�c�p�[�g�ŃA�N�Z�X�o����I�u�W�F�N�g�̊��N���X
/// �J��UI�̔ԍ��Ɖ������邩�̃e�L�X�g������
/// </summary>
class ManagementPartObjectBase : public GameObject
{
protected:
	int accessUINum_;
	std::string actionName_;
public:
	ManagementPartObjectBase(Object* parent, std::string name);
	~ManagementPartObjectBase();
	int GetAccessUINumber() { return accessUINum_; }
	std::string GetActionName() { return actionName_; }
};

