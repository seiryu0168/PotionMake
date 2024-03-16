#pragma once
#include"../Engine/GameObject/GameObject.h"
#include"../Engine/Time.h"
class SnowCone_Cup;
class SnowCone_ToppingSumple;
class SnowCone_SyrupSumple;
class SnowConeMaker_Topping : public GameObject
{
private:
	std::shared_ptr<Time::Watch> timer_;
	int playerNum_;
	int coneSizeText_;
	SnowCone_Cup* snowCone_;
	SnowCone_ToppingSumple* toppingSumple_;
	SnowCone_SyrupSumple* syrupSumple_;
public:
	SnowConeMaker_Topping(Object* parent);
	~SnowConeMaker_Topping();

	void Initialize() override;
	void Update() override;
	void SetTopping();
	/// <summary>
	/// プレイヤーの番号を指定
	/// </summary>
	/// <param name="num">番号(コントローラーとかの操作に影響する)</param>
	void SetPlayerNumber(int num) { playerNum_ = num; }
	/// <summary>
	/// UIのリセット
	/// </summary>
	void ResetSelectUI();
	void Release() override;

};

