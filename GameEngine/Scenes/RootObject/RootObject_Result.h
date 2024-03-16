#pragma once
#include"../../Engine/GameObject/Object.h"
#include"../../Engine/Time.h"
class RootObject_Result : public Object
{
	//std::shared_ptr<Time::Watch> timer_;
	//bool isSceneChange_;
public:
	RootObject_Result();
	~RootObject_Result();
	void Initialize() override;
	void Update() override;
	void SceneChange();
	void Release() override;
};

