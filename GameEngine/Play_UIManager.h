#pragma once
#include"Engine/GameObject/GameObject.h"
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
	void Release() override;

};

