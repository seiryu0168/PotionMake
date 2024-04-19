#pragma once
#include"Engine/GameObject/GameObject.h"
class P_CP_Player_ItemGetter : public GameObject
{
	int targetItemNum_;
	GameObject* hitItem_;
public:
	P_CP_Player_ItemGetter(Object* parent);
	~P_CP_Player_ItemGetter();

	void Initialize() override;
	void Start() override;
	void Update() override;
	int GetItemNumber() { return targetItemNum_; }
	void KillHitObject() { if (hitItem_ != nullptr)hitItem_->KillMe(); hitItem_ = nullptr; }
	void Release() override;

	void OnCollisionStay(GameObject* pTarget) override;
};

