#pragma once
#include"SnowCone_ToppingMenu.h"

class SnowCone_ToppingSelect : public SnowCone_ToppingMenu
{
private:
	int selectFrame_;
	int toppingText_;
public:
	SnowCone_ToppingSelect(Object* parent);
	~SnowCone_ToppingSelect();

	void Initialize() override;
	void Update() override;
	/// <summary>
	/// 入力
	/// </summary>
	void Input();
	/// <summary>
	///	カーソルを移動
	/// </summary>
	void Move();
	/// <summary>
	/// 今選んでいるトッピングの番号を取得
	/// </summary>
	/// <returns>トッピングの番号</returns>
	int GetToppingNum() { return selectNum_; }
	/// <summary>
	/// UIのリセット
	/// </summary>
	void UIReset();
	void Release() override;
};

