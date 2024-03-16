#pragma once
#include "Framework.h"

//�I����
enum class CHOICES : int
{
	ABOVE,
	UNDER,
	LEFT,
	RIGHT
};

class FindDifference : public Framework
{
	int Penalty_;	//�����ΏۂƂȂ�v���C���[

	CHOICES Direction_;	//�ԈႢ��\���������

	std::vector<int> Points_;	//�v���C���[���Ƃ̓��_
public:
	FindDifference(Object* parent);
	~FindDifference();

	void Initialize() override;
	void Release() override;

	/// <summary>Player��������͂��擾����</summary>
	/// <param name="select">�I��������</param>
	/// <param name="Playernum">�v���C���[�̔ԍ�</param>
	void SendData(CHOICES select, int Playernum);
};

