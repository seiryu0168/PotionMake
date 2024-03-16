#pragma once
#include<set>
#include"ECS.h"
//�e�R���|�[�l���g�̐��������V�X�e���N���X�̊��N���X
class System
{
public:
	std::set<Entity> entities_;
	System() :entities_(){};
	~System() {};
	//������
	virtual void Init() {};
	//�X�V
	virtual void Update() {};
	//�`��
	virtual void Draw(int drawLayer = 0) {};
	//�R���|�[�l���g���������ǂ���
	virtual void CheckRemove() {};
	//�R���|�[�l���g�S����
	virtual void Release() {};
};

