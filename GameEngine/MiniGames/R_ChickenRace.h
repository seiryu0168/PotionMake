#pragma once
#include "../Result_Multi.h"

//�`�L�����[�X�̃��U���g�N���X
class R_ChickenRace : public Result_Multi
{
public:
	R_ChickenRace(Object* parent);
	~R_ChickenRace();

	void MoreInfo() override;
};

