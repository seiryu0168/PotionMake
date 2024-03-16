#pragma once
#include "../Result_Multi.h"

//チキンレースのリザルトクラス
class R_ChickenRace : public Result_Multi
{
public:
	R_ChickenRace(Object* parent);
	~R_ChickenRace();

	void MoreInfo() override;
};

