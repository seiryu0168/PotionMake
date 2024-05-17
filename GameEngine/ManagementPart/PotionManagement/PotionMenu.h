#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
///選んだポーションの情報を表示するメニュー 
/// </summary>
class PotionMenu : public GameObject
{
private:
	int sellButtonImageNum_;
	int disposeButtonImageNum_;
	int cancelButtonImageNum_;

	int hAudio_Select_;
	int hAudio_Cancel_;
	int hAudio_Confirm_;
	bool isConfirm_;
public:
	PotionMenu(Object* parent);
	~PotionMenu();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateMenu(int potionNum, const std::string& name,int price, const XMFLOAT3& color,bool isConfirm);
	void Release() override;
};

