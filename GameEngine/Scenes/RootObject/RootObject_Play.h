#pragma once
#include"../../Engine/GameObject/Object.h"
class RootObject_Play : public Object
{
public:
	RootObject_Play();
	~RootObject_Play();
	void Initialize() override;
	void Update() override;
	void StaticUpdate() override;
	void Release() override;
};