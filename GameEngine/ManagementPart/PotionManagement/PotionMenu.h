#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
///選んだポーションの情報を表示するメニュー 
/// </summary>
class PotionMenu : public GameObject
{
private:
	int sellButtonImageNum_;
	int disposeButtonImageNum_;
	int cancelButtonImageNum_;
	bool isConfirm_;
public:
	PotionMenu(Object* parent);
	~PotionMenu();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateMenu(int potionNum, const std::string& name, const XMFLOAT3& color,bool isConfirm);
	void Release() override;
};

