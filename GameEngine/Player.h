#pragma once
#include"Engine/GameObject/GameObject.h"

class Play_ManagementPart_BaseUI;

/// <summary>
/// ÉvÉåÉCÉÑÅ[
/// </summary>
class Player : public GameObject
{
private:

	Play_ManagementPart_BaseUI* UIBase_;

	std::string collisionObjectName_;
	int collisionUINum_;
	Object* UIManagerObject_;
	XMVECTOR moveVec_;
	float speed_;
	XMVECTOR cameraTargetVec_;
	XMFLOAT2 cameraRotate_;
	float rotateUperLimitY_;
	float rotateDownerLimitY_;
	float moveTime_;
public:
	Player(Object* parent);
	~Player();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void CameraControll();
	void Release() override;
	void OnCollisionStay(GameObject* pTarget) override;
	void OnCollisionExit(GameObject* pTarget) override;
	//void OnCollision(Object* pTarget) override;
};

