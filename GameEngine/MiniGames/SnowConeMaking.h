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
	/// �Q�[�����n�܂�O�̎菇����
	/// </summary>
	void Stay();
	/// <summary>
	/// �J�E���g�_�E��
	/// </summary>
	void Count();
	/// <summary>
	/// �Q�[���{��
	/// </summary>
	void Play();
	/// <summary>
	/// �Q�[���I����
	/// </summary>
	//void Finish();
	//�����X�̃J�b�v���X�g�b�N�ɓ����
	void AddCup(SnowCone_Cup* cup);
	//�X�R�A�̍X�V
	void ScoreUpdate(int score);
	/// <summary>
	/// �����X�̕]��
	/// </summary>
	/// <param name="size">�����X�̃T�C�Y</param>
	/// <param name="syrup">�V���b�v�̎��</param>
	/// <param name="topping">�g�b�s���O�̎��</param>
	void Evaluation(float size,int syrup,int topping);
	/// <summary>
	/// �����X���X�g�b�N������o��
	/// </summary>
	/// <returns>�����X�̃|�C���^</returns>
	SnowCone_Cup* GetCup();


	void NotifiedUpdateT();
	void NotifiedUpdateF();
	void Release()override;
};

