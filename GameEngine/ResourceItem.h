#pragma once
#include"ItemBase.h"
/// <summary>
/// �|�[�V��������p�̑f��
/// </summary>
class ResourceItem : public ItemBase
{
	XMFLOAT3 imagePos_;
	//Object* potObject_;
public:
	ResourceItem(Object* parent);
	~ResourceItem();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};