#pragma once
#include"../Engine/GameObject/GameObject.h"
class SnowCone_SyrupSumple : public GameObject
{
private:
	int currentNum_;
	XMFLOAT3 sumplePos_;
	float offsetPosY_;
	float easingTime_;
	bool isMove_;
public:
	SnowCone_SyrupSumple(Object* parent);
	~SnowCone_SyrupSumple();

	void Initialize() override;	
	void Update() override;
	void ChangeSumple(int num);
	void SetSyrupSize(float size);
	int  GetSumpleImageNum() { return currentNum_; }
	void MoveSumple(float yPos);
	void Move() { isMove_ = true; }
	void Reset();
	void Release() override;
};

