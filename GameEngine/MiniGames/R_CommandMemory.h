#pragma once
#include "../Result_Multi.h"

class R_CommandMemory : public Result_Multi
{
public:
	R_CommandMemory(Object* parent);
	~R_CommandMemory();

	void MoreInfo() override;
};
