#pragma once
#include"../DirectX_11/Texture.h"
#include<string>
#include<vector>
#include<memory>
namespace TextureManager
{
	int Load(const std::string& fileName);
	int StaticLoad(const std::string& fileName);
	Texture* GetTexture(int textureHandle);
	Texture* GetStaticTexture(int textureHandle);
	void Release();
	void StaticTextureRelease();
}