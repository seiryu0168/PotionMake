#pragma once
#include"ManagementPartObjectBase.h"
class Play_ManagementPart_Door : public ManagementPartObjectBase
{
private:
public:
	Play_ManagementPart_Door(Object* parent);
	~Play_ManagementPart_Door();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

