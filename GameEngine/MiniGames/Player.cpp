#include "Player.h"

Player::Player(Object* parent, const std::string& name)
	: GameObject(parent, name)
{
	auto list = parent->GetChildList();
	int id = 0;
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (itr->get()->GetObjectName() == name)
			++id;
	}
	Playerid_ = id;
}
