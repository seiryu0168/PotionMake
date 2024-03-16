#include "SnowCone_ScoreManager.h"

SnowCone_ScoreManager::SnowCone_ScoreManager()
{
}

SnowCone_ScoreManager::SnowCone_ScoreManager(const unsigned short& playerCount, int initScore)
	:ScoreManager(playerCount, initScore)
{
	for (int i = 0; i < playerCount; i++)
	{
		playerScores_.push_back(initScore);
	}
}

SnowCone_ScoreManager::~SnowCone_ScoreManager()
{
}

void SnowCone_ScoreManager::Init(const unsigned short& playerCount, int initScore)
{
	for (int i = 0; i < playerCount; i++)
	{
		playerScores_.push_back(initScore);
	}
}

void SnowCone_ScoreManager::ScoreUpdate(int& score)
{
	playerScores_[0] += score;
}

int SnowCone_ScoreManager::GetScore()
{
	return playerScores_[0];
}
