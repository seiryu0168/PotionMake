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

	std::vector<int> cmList_;	//�R�}���h�̔z��
	std::vector<int>::iterator itr_;	//�R�}���h�̔z��ɑ΂���C�e���[�^
	int NowPlayer_;				//���ݑ��쒆�̃v���C���[
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

	//����ꂽ�{�^����id�������Ă��邩���؂���
	void sendCommand(int Button, int Playerid);
};

