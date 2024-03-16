#pragma once
#include"../Engine/GameObject/GameObject.h"
class Shooting_Gun : public GameObject
{
	unsigned short playerNum_;
	XMVECTOR frontVec_;
	int bulletCount_;
	int hAudio_Shot_;
	size_t textNum_;
public:
	Shooting_Gun(Object* parent);
	~Shooting_Gun();
	void Initialize() override;
	void Update() override;
	//弾発射
	void Shot(const XMVECTOR& dir);
	//弾を発射する位置取得
	XMVECTOR GetShotPos();
	//描画するかどうか設定
	void SetDraw(bool isDraw);
	//残弾数取得
	int& GetBulletCount() { return bulletCount_; }
	//撃った数を取得
	int GetShotCount();
	//リロード
	void Reload();
	//プレイヤー番号設定
	void SetPlayerNum_(const unsigned short& num) { playerNum_ = num; }
	void Release() override;
};

