#pragma once
#include"Engine/GameObject/GameObject.h"
class PotionMenu : public GameObject
{
private:
	int sellButtonImageNum_;
	int disposeButtonImageNum_;
public:
	PotionMenu(Object* parent);
	~PotionMenu();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void CreateMenu(int potionNum, const std::string& name, const XMFLOAT3& color);
	void Release() override;
};

