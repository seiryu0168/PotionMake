#pragma once
#include"Engine/GameObject/GameObject.h"
class TestObject : public GameObject
{
private:
	int hModel_;
	int time_;
	XMVECTOR vPos_;
public:
	TestObject(Object* parent);
	~TestObject();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(Object* target) override;
};

