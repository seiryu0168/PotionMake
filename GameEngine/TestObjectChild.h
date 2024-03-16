#pragma once
#include"Engine/GameObject/GameObject.h"
class TestObjectChild : public GameObject
{
private:
	int hModel_;
	int time_;
public:
	TestObjectChild(Object* parent);
	~TestObjectChild();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(Object* target) override;
};

