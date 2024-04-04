#pragma once
#include"Engine/GameObject/GameObject.h"
class PotionStock : public GameObject
{
	int potionNum_;
	std::string potionName_;
	std::vector<float> potionStatus_;
public:
	PotionStock(Object* parent);
	~PotionStock();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetPotionStatus_(int potionNum,std::string name,int sts0, int sts1, int sts2, int sts3, int sts4);
	void Release() override;
};

