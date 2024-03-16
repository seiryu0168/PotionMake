#pragma once
#include "../Engine/GameObject/Object.h"
#include "../Engine/Time.h"
#include "../Engine/Components/Text.h"

//�~�j�Q�[���̘g�g�݂ƂȂ���N���X
class Framework : public Object
{
	std::vector<Text> MenuTexts_;
	int Select_;					//�I�����Ă���e�L�X�g�̔ԍ�
	bool CallPause_;				//�|�[�Y���Ă΂�Ă��邩
	int Privilege_;					//�|�[�Y��ʂ̑��쌠�����v���C���[
	int Frame_;						//���[�h�ύX�ɂȂ��Ă��牽�t���[���o�߂�����
	bool isFinish_;

	enum class STATE
	{
		PLAY = 0,
		PAUSE,
		SCENE_CHANGE
	};

	STATE nowState_;

	void PauseMenu();
	void Conduct();					//�|�[�Y�̉����ꂽ�{�^�����̋������Ǘ�
	void Load();
	void State_Pause();
	void State_SceneChange();	
protected:
	int Players_;	//�v���C�l��
	Time::Watch GameTime_;	//�~�j�Q�[���̎���

	//�v���C�l���������v���C���[�̐������s��
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
	//StaticUpdate�ŌĂяo����pause�������\�ɂȂ�
	void Pause();

public:
	Framework(Object* parent, const std::string& name);
	virtual ~Framework();

	void Draw() override final;
};

