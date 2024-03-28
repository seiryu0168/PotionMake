#pragma once
#include"ItemBase.h"
/// <summary>
/// �|�[�V��������p�̑f��
/// </summary>
class ResourceItem : public ItemBase
{
private:
	XMFLOAT3 imagePos_;
	bool haveItem_;
	//Object* potObject_;
public:
	ResourceItem(Object* parent);
	~ResourceItem();
	void Initialize() override;
	void Start() override;
	void Update() override;
	bool HaveItem() { return haveItem_; }
	void SetItem(bool item) { haveItem_ = item; }
	void SetItem(int itemNum);
	void Release() override;
};