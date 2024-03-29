#pragma once
#include"ItemBase.h"
/// <summary>
/// �|�[�V��������p�̑f��
/// </summary>
class ResourceItem : public ItemBase
{
private:

	XMFLOAT3 imagePos_;
	GameObject* potObject_;
public:
	ResourceItem(Object* parent);
	~ResourceItem();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetItemNum(int num) { itemNum_ = num; }
	int GetItemNum() { return itemNum_; }
	void Release() override;
};