#pragma once
#include"Engine/GameObject/GameObject.h"

class Play_ManagementPart_BaseUI;

/// <summary>
/// ÉvÉåÉCÉÑÅ[
/// </summary>
class Player : public GameObject
{
private:
	std::string collisionObjectName_;
	XMVECTOR moveVec_;
	int collisionUINum_;
	float speed_;
	XMVECTOR cameraTargetVec_;
	XMFLOAT2 cameraRotate_;
	float rotateUperLimitY_;
	float rotateDownerLimitY_;
	float moveTime_;
	//Play_ManagementPart_BaseUI* UIBase_;
	Object* UIManagerObject_;



public:
	Player(Object* parent,std::string name);
	~Player();
	//void Initialize() override;
	//void Start() override;
	//void Update() override;
	void MoveControll();
	void CameraControll();
	float GetSpeed() { return speed_; }
	Object* GetUIManager() { return UIManagerObject_; }
	void SetUIManager(Object* uiManager);
	void Release() override;
	//void OnCollisionStay(GameObject* pTarget) override;
	//void OnCollisionExit(GameObject* pTarget) override;
	//void OnCollision(Object* pTarget) override;
};

