#pragma once
#include"../ScoreManager.h"
class SnowCone_ScoreManager : public ScoreManager<int>
{
public:
	SnowCone_ScoreManager();
	SnowCone_ScoreManager(const unsigned short& playerCount,int initScore);
	~SnowCone_ScoreManager();

	void Init(const unsigned short& playerCount, int initScore);
	void ScoreUpdate(int& score);
	int GetScore();
};

