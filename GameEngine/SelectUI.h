#pragma once
#include"Engine/GameObject/GameObject.h"
#include"Engine/Time.h"
#include <map>

class SelectUI : public GameObject
{
private:
	enum class SELECT_STATE
	{
		STATE_INPUT = 0,
		STATE_MOVE,
		STATE_SELECTED,
	};
	std::shared_ptr<Time::Watch> timer_;
	short moveDir_;
	SELECT_STATE state_;
	int buttonCount_;
	int buttonNum_;
	int filterNum_;
	unsigned short playCount_;

	int countTextNum_;
	int moveTime_;
	int inputInterval_;

	int ArrowFrame_;	//矢印を動かすためのフレーム数
	int ArrowId_[2];
	//入力
	void Input();
	//ボタンが動く処理
	void Move();
	//ゲームを選んだ後の処理
	void Selected();
	std::vector<int> moveUIList_;
	std::vector<int> playerCountList_;
	std::vector<XMFLOAT3> basePosList_;
	std::map<int, std::vector<int>::iterator> Selection_;
	void ItrIncrement();
	void ItrDecrement();
	void UIPositioning();

	void ArrowLoad();
	void ArrowMove();
public:
	SelectUI(Object* parent);
	~SelectUI();
	void Initialize() override;
	void Update() override;
	void PlayerCount(const int& padButton);
	void MoveButton(float ratio);
	void PushedButton(int buttonNum);
	void Release() override;
};

