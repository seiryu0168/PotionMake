#pragma once
#include "../../ManagementPartObjectBase.h"
/// <summary>
/// ポーション政策を行う机
/// </summary>
class Play_ManagementPart_CraftTable : public ManagementPartObjectBase
{
private:
public:
	Play_ManagementPart_CraftTable(Object* parent);
	~Play_ManagementPart_CraftTable();
	void Initialize() override;
	void Update() override;
	void Release() override;

};

