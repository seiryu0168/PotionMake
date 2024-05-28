#pragma once
#include"Engine/GameObject/GameObject.h"

/// <summary>
/// 新聞を表示するクラス
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

