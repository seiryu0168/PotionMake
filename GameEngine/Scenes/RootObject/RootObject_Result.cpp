#include "RootObject_Result.h"
#include"../../InterSceneData.h"
#include"../../StaticResource.h"
#include"../../Engine/Components/Transform.h"

RootObject_Result::RootObject_Result()
{
	//isSceneChange_ = false;
	Transform transform;
	AddComponent<Transform>(transform);
}

RootObject_Result::~RootObject_Result()
{
}
	
void RootObject_Result::Initialize()
{
}

void RootObject_Result::Update()
{
	
}

void RootObject_Result::SceneChange()
{

}

void RootObject_Result::Release()
{
}
