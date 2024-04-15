#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// â¡çHï˚ñ@ÇÃUI
/// </summary>
class P_MP_CraftUI_ProcessUI : public GameObject
{
private:
	bool isClicked_;
	int processNum_;
	std::string name_;
	GameObject* craftPotObject_;
public:
	P_MP_CraftUI_ProcessUI(Object* parent);
	~P_MP_CraftUI_ProcessUI();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetProcessImage(std::string imageName);
	void SetProcessData(const std::string processName);
	void SetProcessNumber(int num) { processNum_ = num; }
	void ActiveUI(bool isActive);
	void CreateBase(XMFLOAT3 uiPos);
	void Release() override;
};

