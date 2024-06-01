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
	bool canControll_;
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
	virtual void MoveControll();
	virtual void CameraControll();
	float& GetSpeed() { return speed_; }
	void SetControllFlag(bool flag) { canControll_ = flag; }
	bool CanControll() { return canControll_; }
	XMVECTOR& GetMoveVec() { return moveVec_; }
	XMVECTOR& GetCameraTargetVec() { return cameraTargetVec_; }
	XMFLOAT2& cameraRotate() { return cameraRotate_; }
	Object* GetUIManager() { return UIManagerObject_; }
	void SetUIManager(Object* uiManager);
	void Release() override;
};

