#pragma once
#include "Framework.h"
#include "../Engine/Components/Image.h"

class GameObject;

class ChickenRace : public Framework
{
private:
	enum class STATE
	{
		prologue = 0,
		countdown,
		play,
		finish
	} state_;
	int TargetTime;	//–Ú•W‚Æ‚È‚éŽžŠÔ
	std::vector<float> PlayersTime_;
	Text* text_;

	std::unique_ptr<Time::Watch> watch_;

	Image* BG_;

	int hAudio_;
	int Delay_;

	void Prologue();
	void Countdown();
	void Play();
	void To_Finish();
public:
	ChickenRace(Object* parent);
	~ChickenRace();

	void Initialize() override;
	void Update() override;
	void Release() override;

	void SendTime(Object* target, float time);
	int GetTarget() const { return TargetTime; }
};

