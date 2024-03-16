#pragma once
#include<unordered_map>
#include<memory.h>
#include"../DirectX_11/Fbx.h"
#include"../DirectX_11/Texture.h"
#include"../Components/Transform.h"
namespace ModelManager_ECSver
{
	std::shared_ptr<Fbx> Load(const std::string& fileName);
	void Release();
};

