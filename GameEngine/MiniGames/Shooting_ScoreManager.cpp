#include "Shooting_ScoreManager.h"

Shooting_ScoreManager::Shooting_ScoreManager()
	:ScoreManager()
{
}

Shooting_ScoreManager::Shooting_ScoreManager(const unsigned short& playerCount, int initScore)
	:ScoreManager(playerCount,initScore)
{
}

Shooting_ScoreManager::~Shooting_ScoreManager()
{
}

void Shooting_ScoreManager::Init(const unsigned short& playerCount, int initScore)
{
	//引数で初期化
	for (int i = 0; i < playerCount; i++)
	{
		playerScores_.push_back(initScore);
	}
}

void Shooting_ScoreManager::ScoreUpdate(const unsigned short& playerNum, int score)
{
	//引数のプレイヤーのスコアの更新
	if (playerNum < playerScores_.size())
	{
		playerScores_[playerNum] += score;
		playerScores_[playerNum] = std::max<int>(0, playerScores_[playerNum]);
	}
}

int Shooting_ScoreManager::GetScore(const unsigned short& playerNum)
{
	if(playerNum<playerScores_.size())
	return playerScores_[playerNum];

	return -1;
}
