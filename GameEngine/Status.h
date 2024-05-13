#pragma once
#include"UIBase.h"
class Status : public UIBase
{
	int statusImageNum_;
	int closeButtonNum_;
	int nameTextNum_;
	int moneyTextNum_;
	bool isClickedButton_;
public:
	Status(Object* parent);
	~Status();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

