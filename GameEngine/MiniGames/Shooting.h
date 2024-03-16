#pragma once
#include"Framework.h"
#include"../Engine/Time.h"
#include"Shooting_ScoreManager.h"
#include"Shooting_ScoreUI.h"
class Shooting : public Framework
{
	enum class PLAY_STATE
	{
		STATE_STAY = 0,
		STATE_PLAY,
		STATE_FINISH,
	};
	std::unique_ptr<Time::Watch> time_;
	PLAY_STATE state_;
	Shooting_ScoreManager scoreManager_;
	int playerCount_;
	Shooting_ScoreUI ui;
public:
	Shooting(Object* parent);
	~Shooting();

	void Initialize() override;
	void Update() override;
	//�X�R�A�̍X�V
	void ScoreUpdate(const unsigned short& playernum, int score);
	//STATE_STAY�̎��̏���
	void Stay();
	//STATE_PLAY�̎��̏���
	void Play();
	void Release() override;
	void StaticUpdate() override;
	void NotifiedUpdateT() override;
	void NotifiedUpdateF() override;
};

