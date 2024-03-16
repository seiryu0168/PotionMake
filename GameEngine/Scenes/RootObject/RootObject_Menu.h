#pragma once
#include"../../Engine/GameObject/Object.h"
class RootObject_Menu : public Object
{
public:
	RootObject_Menu();
	~RootObject_Menu();
	void Initialize() override;
	void Release() override;
};

