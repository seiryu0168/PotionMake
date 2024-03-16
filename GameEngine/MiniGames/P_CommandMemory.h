#pragma once
#include "Player.h"

class CommandMemory;

class P_CommandMemory : public Player
{
	CommandMemory* memory_;
public:
	P_CommandMemory(Object* parent);
	~P_CommandMemory();

	void Initialize() override;
	void Update() override;
	void Release() override;
};

