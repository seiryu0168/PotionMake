#pragma once
#include"../Engine/GameObject/GameObject.h"
class Shooting_TergetGift : public GameObject
{
	int score_;
	int hAudio_CollisionSound_;
	bool isHit_;
	float fallSpeed_;
public:
	Shooting_TergetGift(Object* parent);
	~Shooting_TergetGift();

	void Initialize() override;
	void Update() override;
	void Fall();
	void OnCollision(Object* target) override;
	//スコアの設定
	void SetScore(const int& score) { score_ = score; }
	//音のハンドル設定
	void SetAudioHandle(int handle) { hAudio_CollisionSound_ = handle; }
	//スコア取得
	int& GetScore() { return score_; }
	void Release();
};

