#pragma once
#include "../Engine/GameObject/Object.h"
#include "../Engine/Time.h"
#include "../Engine/Components/Text.h"

//ミニゲームの枠組みとなる基底クラス
class Framework : public Object
{
	std::vector<Text> MenuTexts_;
	int Select_;					//選択しているテキストの番号
	bool CallPause_;				//ポーズが呼ばれているか
	int Privilege_;					//ポーズ画面の操作権を持つプレイヤー
	int Frame_;						//モード変更になってから何フレーム経過したか
	bool isFinish_;

	enum class STATE
	{
		PLAY = 0,
		PAUSE,
		SCENE_CHANGE
	};

	STATE nowState_;

	void PauseMenu();
	void Conduct();					//ポーズの押されたボタン毎の挙動を管理
	void Load();
	void State_Pause();
	void State_SceneChange();	
protected:
	int Players_;	//プレイ人数
	Time::Watch GameTime_;	//ミニゲームの時間

	//プレイ人数分だけプレイヤーの生成を行う
	template<class T>
	void PlayerInitialize()
	{
		for (int i = 0; i < Players_; i++)
		{
			auto p = Instantiate<T>(this);
		}
	}
	void Finish();
	void GameFinish(bool isFinish);
	//StaticUpdateで呼び出すとpause処理が可能になる
	void Pause();

public:
	Framework(Object* parent, const std::string& name);
	virtual ~Framework();

	void Draw() override final;
};

