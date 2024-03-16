#pragma once
#include"Framework.h"
#include"../Engine/Time.h"
#include"SnowCone_ScoreManager.h"

class SnowCone_Cup;
class SnowConeMaking : public Framework
{
private:
	enum class PLAY_STATE
	{
		STATE_STAY = 0,
		STATE_COUNT,
		STATE_PLAY,
		STATE_FINISH,
	};
	std::vector<SnowCone_Cup*> cupList_;
	std::unique_ptr<Time::Watch> time_;
	std::vector<int> shavedCupList_;
	std::vector<int> shavedCupSize_;
	PLAY_STATE state_;
	SnowCone_ScoreManager scoreManager_;
	int progressImageNum_;
	int explanationNum_;
	int explanationNum2_;
	int blackImage_;
	char copuntFlag_;
	int timeText_;
	

public:
	SnowConeMaking(Object* parent);
	~SnowConeMaking();
	void Initialize() override;
	void Update() override;
	void StaticUpdate() override;
	/// <summary>
	/// ゲームが始まる前の手順説明
	/// </summary>
	void Stay();
	/// <summary>
	/// カウントダウン
	/// </summary>
	void Count();
	/// <summary>
	/// ゲーム本編
	/// </summary>
	void Play();
	/// <summary>
	/// ゲーム終了後
	/// </summary>
	//void Finish();
	//かき氷のカップをストックに入れる
	void AddCup(SnowCone_Cup* cup);
	//スコアの更新
	void ScoreUpdate(int score);
	/// <summary>
	/// かき氷の評価
	/// </summary>
	/// <param name="size">かき氷のサイズ</param>
	/// <param name="syrup">シロップの種類</param>
	/// <param name="topping">トッピングの種類</param>
	void Evaluation(float size,int syrup,int topping);
	/// <summary>
	/// かき氷をストックから取り出す
	/// </summary>
	/// <returns>かき氷のポインタ</returns>
	SnowCone_Cup* GetCup();


	void NotifiedUpdateT();
	void NotifiedUpdateF();
	void Release()override;
};

