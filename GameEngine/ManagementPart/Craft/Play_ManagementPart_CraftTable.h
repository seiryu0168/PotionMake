#pragma once
#include "../../ManagementPartObjectBase.h"
/// <summary>
/// �|�[�V����������s����
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

