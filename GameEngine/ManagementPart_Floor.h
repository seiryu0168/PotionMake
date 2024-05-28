#pragma once
#include"Engine/GameObject/GameObject.h"

/// <summary>
/// �o�c�p�[�g�̏��I�u�W�F�N�g
/// </summary>
class ManagementPart_Floor : public GameObject
{
private:
	float rotate_;
	int hAudio_BGM_;
public:
	ManagementPart_Floor(Object* parent);
	~ManagementPart_Floor();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

