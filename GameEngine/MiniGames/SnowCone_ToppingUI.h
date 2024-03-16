#pragma once
#include"../Engine/GameObject/GameObject.h"

class SnowCone_SyrupSelect;
class SnowCone_ToppingSelect;
class Image;
enum class SELECT_MODE
{
	MODE_SYRUP = 0,
	MODE_TOPPING,
	MODE_COMPLETE,
};
class SnowCone_ToppingUI : public GameObject
{
private:
	SnowCone_SyrupSelect* syrupSelect_;
	SnowCone_ToppingSelect* toppingSelect_;
	SELECT_MODE mode_;
public:
	SnowCone_ToppingUI(Object* parent);
	~SnowCone_ToppingUI();

	void Initialize() override;
	void Update() override;
	/// <summary>
	/// シロップの番号取得
	/// </summary>
	/// <returns>シロップの番号</returns>
	int GetSyrupData();
	/// <summary>
	/// トッピングの番号取得
	/// </summary>
	/// <returns>トッピングの番号</returns>
	int GetToppingData();
	/// <summary>
	/// 今選ばれているシロップの画像を取得する
	/// </summary>
	/// <returns>画像</returns>
	Image GetCurrentSyrupImage();
	/// <summary>
	/// 今選ばれているトッピングの画像を取得する
	/// </summary>
	/// <returns>画像</returns>
	Image GetCurrentToppingImage();
	/// <summary>
	/// シロップを選ぶかトッピングを選ぶかのモードを切り替える
	/// </summary>
	/// <param name="mode">モード</param>
	void ModeChange(SELECT_MODE mode);
	/// <summary>
	/// UIをリセット
	/// </summary>
	void ResetUI();
	void Release() override;
};

