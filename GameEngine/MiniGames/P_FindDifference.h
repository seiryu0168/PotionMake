#pragma once
#include "Player.h"

class FindDifference;

class P_FindDifference : public Player
{
	FindDifference* pFD_;
public:
	P_FindDifference(Object* parent);
	~P_FindDifference();

	void Initialize() override;
	void Update() override;
	void Release() override;
};

