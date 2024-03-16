#pragma once
#include"../Engine/GameObject/GameObject.h"
class SnowCone_ToppingSumple : public GameObject
{
private:
	XMFLOAT3 sumplePos_;
	int currentNum_;
	float offsetPosY_;
	float easingTime_;
	bool isMove_;
		 
public:
	SnowCone_ToppingSumple(Object* parent);
	~SnowCone_ToppingSumple();

	void Initialize() override;
	void Update() override;
	/// <summary>
	/// サンプル画像を変える
	/// </summary>
	/// <param name="num">表示するサンプル番号</param>
	void ChangeSumple(int num);
	/// <summary>
	/// サンプルの大きさを設定
	/// </summary>
	/// <param name="size">かき氷の大きさ</param>
	void SetSumpleSize(float size);
	/// <summary>
	/// かき氷を受け取る時に動かす
	/// </summary>
	/// <param name="pos">位置</param>
	void MoveSumple(float pos);
	/// <summary>
	/// 動くかどうかの設定
	/// </summary>
	void Move() { isMove_ = true; }
	/// <summary>
	/// 各パラメータのリセット
	/// </summary>
	void Reset();
	void Release() override;

};

