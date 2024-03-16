#pragma once
#include"../Engine/GameObject/GameObject.h"
class SnowCone_ToppingSumple : public GameObject
{
private:
	XMFLOAT3 sumplePos_;
	int currentNum_;
	float offsetPosY_;
	float easingTime_;
	bool isMove_;
		 
public:
	SnowCone_ToppingSumple(Object* parent);
	~SnowCone_ToppingSumple();

	void Initialize() override;
	void Update() override;
	/// <summary>
	/// �T���v���摜��ς���
	/// </summary>
	/// <param name="num">�\������T���v���ԍ�</param>
	void ChangeSumple(int num);
	/// <summary>
	/// �T���v���̑傫����ݒ�
	/// </summary>
	/// <param name="size">�����X�̑傫��</param>
	void SetSumpleSize(float size);
	/// <summary>
	/// �����X���󂯎�鎞�ɓ�����
	/// </summary>
	/// <param name="pos">�ʒu</param>
	void MoveSumple(float pos);
	/// <summary>
	/// �������ǂ����̐ݒ�
	/// </summary>
	void Move() { isMove_ = true; }
	/// <summary>
	/// �e�p�����[�^�̃��Z�b�g
	/// </summary>
	void Reset();
	void Release() override;

};

