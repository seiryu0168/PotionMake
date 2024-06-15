#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// �t�B�[���h�ɗ����Ă���A�C�e���ɃA�N�Z�X����N���X
/// </summary>
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
	void KillHitObject() { if (hitItem_ != nullptr)hitItem_->SetActive(false); hitItem_ = nullptr; }
	void Release() override;

	void OnCollisionStay(GameObject* pTarget) override;
};

