#pragma once
#include"ManagementPartObjectBase.h"
class Play_ManagementPart_Shelf : public ManagementPartObjectBase
{
private:
public:
	Play_ManagementPart_Shelf(Object* parent);
	~Play_ManagementPart_Shelf();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

