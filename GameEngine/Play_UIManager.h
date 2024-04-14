#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// 全てのUIの親
/// ここから全UIが作られているので、アクセスはここから行う
/// </summary>
class Play_UIManager : public GameObject
{
private:
	int accessUINum_;
public:
	Play_UIManager(Object* parent);
	~Play_UIManager();
	void Initialize() override;
	void Update() override;	
	void AccessUI(int uiNum);
	bool IsAccessUI();
	void Release() override;

};

