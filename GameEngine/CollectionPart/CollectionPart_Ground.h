#pragma once
#include "../Engine/GameObject/GameObject.h"
/// <summary>
/// �n�ʂ̃I�u�W�F�N�g
/// </summary>
class CollectionPart_Ground : public GameObject
{
public:
	CollectionPart_Ground(Object* parent);
	~CollectionPart_Ground();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

