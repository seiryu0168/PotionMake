#pragma once
#include<unordered_map>
#include<memory>
#include"../DirectX_11/Sprite.h"
namespace ImageManager_ECSver
{
	std::shared_ptr<Sprite> Load(const std::string& fileName);
	std::shared_ptr<Sprite> StaticLoad(const std::string& fileName);
	void Release();
	void StaticImageRelease();
};

