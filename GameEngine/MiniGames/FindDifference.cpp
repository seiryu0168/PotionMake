#include "FindDifference.h"
#include "P_FindDifference.h"
#include <random>

namespace
{
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_int_distribution tar(0, 3);

	const int Correct = 1;		//�����̎��ɉ��Z�����|�C���g
	const int Incorrect = -3;	//�s�����̎��Ɍ��Z�����|�C���g

	const int NoPenalty = -1;	//�y�i���e�B���N���Ώۂł͂Ȃ����̒l
}

FindDifference::FindDifference(Object* parent)
	: Framework(parent, "FindDifference"), Penalty_(NoPenalty), Direction_(), Points_()
{
}

FindDifference::~FindDifference()
{
}

void FindDifference::Initialize()
{
	Players_ = 2;
	PlayerInitialize<P_FindDifference>();

	//�����_���ɕ��������肷��
	Direction_ = (CHOICES)tar(engine);

	for (int i = 0; i < Players_; i++)
	{
		Points_.push_back(0);
	}
}

void FindDifference::Release()
{
}

void FindDifference::SendData(CHOICES select, int Playernum)
{
	//�y�i���e�B�̑Ώۂł͂Ȃ����Ƃ��m�F
	if (Playernum != Penalty_)
	{
		//�����Ă���ΐ����҂̓��_�����Z���A�y�i���e�B�҂��Ȃ��ɂ���
		if (Direction_ == select)
		{
			Points_[Playernum] += Correct;
			Penalty_ = NoPenalty;
		}
		else
		{
			Points_[Playernum] += Incorrect;
			Penalty_ = Playernum;
		}
	}
}
