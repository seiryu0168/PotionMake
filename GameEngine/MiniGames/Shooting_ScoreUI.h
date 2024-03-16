#pragma once
#include<string>
#include"../Engine/ECS/ECS.h"
class Shooting_ScoreUI
{
	std::vector<Entity> uiEntities_;
public:
	Shooting_ScoreUI();
	~Shooting_ScoreUI();
	//初期化
	void Init(const unsigned short& playerCount, std::string initText);
	//スコアの表示更新
	void TextUpdate(const unsigned short& playerNum, std::string text);
};

