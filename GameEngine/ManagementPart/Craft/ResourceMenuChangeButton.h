#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// 表示を素材と加工方法で切り替えるボタン
/// </summary>
class ResourceMenuChangeButton : public GameObject
{
public:
	ResourceMenuChangeButton(Object* parent);
	~ResourceMenuChangeButton();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

