#pragma once
#include"../Engine/GameObject/GameObject.h"
#include"../Engine/Time.h"

class SnowCone_Cup;
class SnowConeMaker_Shave : public GameObject
{
private:
	std::shared_ptr<Time::Watch> timer_;
	int playerNum_;
	float snowConeSize_;
	SnowCone_Cup* snowCone_;
	int hAudio_Shave_;
public:
	SnowConeMaker_Shave(Object* parent);
	~SnowConeMaker_Shave();
	void Initialize() override;
	void Update() override;
	/// <summary>
	/// �����X�����
	/// </summary>
	void Shave();
	/// <summary>
	/// �v���C���[�̔ԍ����w��
	/// </summary>
	/// <param name="num">�ԍ�(�R���g���[���[�Ƃ��̑���ɉe������)</param>
	void SetPlayerNumber(int num) { playerNum_ = num; }
	void Release() override;

};

