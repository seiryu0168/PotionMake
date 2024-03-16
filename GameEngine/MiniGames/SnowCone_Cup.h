#pragma once
#include"../Engine/GameObject/GameObject.h"
class SnowCone_Cup : public GameObject
{
private:
	enum class SNOWCONE_STATUS
	{
		SHAVE=0,
		STANDBY,
		TOPPING,
		FINISH,
	};
	float coneSize_;
	int coneScore_;

	int iceNum_;
	int cupNum_;
	

	float easingTime_;
	//bool isShaved_;
	//bool isToppinged_;
	bool isEasing_;
	bool haveCup_;
	SNOWCONE_STATUS state_;
	XMFLOAT3 baseImagePos_;
public:
	SnowCone_Cup(Object* parent);
	~SnowCone_Cup();
	void Initialize() override;
	void Update() override;
	void MoveToTopping();
	void MoveToGetCup();
	void MoveToCustomer();
	int GetConeSize();
	float GetConeHeight();
	void SetColor(const XMFLOAT4& color);
	void SetTopping(int topNum);
	void SetConeSize(float size);
	void ChangeDrawTarget(int num);
	void ToppingSetUp();
	void StartEasing() { isEasing_ = true; }
	bool IsEasing() { return isEasing_; }
	void ReleaseCup() { haveCup_ = false; }
	void ChatchCup() { haveCup_ = true; }
	bool HaveCup() { return haveCup_; }
	void Complete(int syrupNum, int toppingNum);
	void RemoveIce();
	void Release() override;
};