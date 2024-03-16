#include "FindDifference.h"
#include "P_FindDifference.h"
#include <random>

namespace
{
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_int_distribution tar(0, 3);

	const int Correct = 1;		//正解の時に加算されるポイント
	const int Incorrect = -3;	//不正解の時に減算されるポイント

	const int NoPenalty = -1;	//ペナルティが誰も対象ではない時の値
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

	//ランダムに方向を決定する
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
	//ペナルティの対象ではないことを確認
	if (Playernum != Penalty_)
	{
		//合っていれば正解者の得点を加算し、ペナルティ者をなしにする
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
