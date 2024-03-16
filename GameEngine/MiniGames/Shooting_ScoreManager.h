#pragma once
#include"../ScoreManager.h"
class Shooting_ScoreManager : public ScoreManager<int>
{
public:
	Shooting_ScoreManager();
	Shooting_ScoreManager(const unsigned short& playerCount,int initScore);
	~Shooting_ScoreManager();
	//初期化
	void Init(const unsigned short& playerCount, int initScore);
	//スコア更新
	void ScoreUpdate(const unsigned short& playerNum, int score);
	//スコア取得
	int GetScore(const unsigned short& playerNum);

};

