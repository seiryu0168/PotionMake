#pragma once
#include"Engine/GameObject/GameObject.h"

/// <summary>
/// �V����\������N���X
/// </summary>
class P_MP_NewsPaper : public GameObject
{
public:
	P_MP_NewsPaper(Object* parent);
	~P_MP_NewsPaper();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

