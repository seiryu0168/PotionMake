#pragma once
#include "Framework.h"
#include <map>

class Image;

class CommandMemory : public Framework
{
	enum class STATE
	{
		PLAY = 0,
		FINISH
	} state_;

	std::vector<int> cmList_;	//コマンドの配列
	std::vector<int>::iterator itr_;	//コマンドの配列に対するイテレータ
	int NowPlayer_;				//現在操作中のプレイヤー
	std::map<WORD, Image*> Images_;
	bool choiced_;
	int moveCount_;

	int hAudio_;

	WORD now_;
	WORD prev_;

	Text* text_;

	Text* RemainingText_;

	void ImageLoad();
public:
	CommandMemory(Object* parent);
	~CommandMemory();

	void Initialize() override;
	void Update() override;
	void Release() override;
	void StaticUpdate() override;

	//送られたボタンのidが合っているか検証する
	void sendCommand(int Button, int Playerid);
};

