#pragma once
#include<set>
#include"ECS.h"
//各コンポーネントの制御をするシステムクラスの基底クラス
class System
{
public:
	std::set<Entity> entities_;
	System() :entities_(){};
	~System() {};
	//初期化
	virtual void Init() {};
	//更新
	virtual void Update() {};
	//描画
	virtual void Draw(int drawLayer = 0) {};
	//コンポーネントを消すかどうか
	virtual void CheckRemove() {};
	//コンポーネント全消去
	virtual void Release() {};
};

