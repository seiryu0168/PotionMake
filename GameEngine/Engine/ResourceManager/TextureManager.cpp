#include "TextureManager.h"
#include"../SAFE_DELETE_RELEASE.h"
namespace TextureManager
{
	struct textureData
	{
		std::shared_ptr<Texture> pTexture_;
		std::string fileName_;
		textureData() : pTexture_(nullptr), fileName_("") {}
	};
	std::vector<std::shared_ptr<textureData>> textureList_;
	std::vector<std::shared_ptr<textureData>> staticTextureList_;
}

int TextureManager::Load(const std::string& fileName)
{
	std::unique_ptr<textureData> pTextureData = std::make_unique<textureData>();
	pTextureData->fileName_ = fileName;
	pTextureData->pTexture_ = nullptr;
	
	for (auto&& itr : textureList_)
	{
		if (fileName == itr->fileName_)
		{
			pTextureData->pTexture_ = itr->pTexture_;

			break;
		}
	}
	if (pTextureData->pTexture_ == nullptr)
	{
		pTextureData->pTexture_ = std::make_shared<Texture>();
		pTextureData->pTexture_->Load(pTextureData->fileName_);
	}
	textureList_.push_back(std::move(pTextureData));
	return (int)textureList_.size() - 1;
}

int TextureManager::StaticLoad(const std::string& fileName)
{
	std::unique_ptr<textureData> pTextureData = std::make_unique<textureData>();
	pTextureData->fileName_ = fileName;
	pTextureData->pTexture_ = nullptr;
	
	for (auto&& itr : staticTextureList_)
	{
		if (fileName == itr->fileName_)
		{
			pTextureData->pTexture_ = itr->pTexture_;

			break;
		}
	}
	if (pTextureData->pTexture_ == nullptr)
	{
		pTextureData->pTexture_ = std::make_shared<Texture>();
		pTextureData->pTexture_->Load(pTextureData->fileName_);
	}
	staticTextureList_.push_back(std::move(pTextureData));
	return (int)staticTextureList_.size() - 1;
	return 0;
}

Texture* TextureManager::GetTexture(int textureHandle)
{
	return textureList_[textureHandle]->pTexture_.get();
}

Texture* TextureManager::GetStaticTexture(int textureHandle)
{
	return staticTextureList_[textureHandle]->pTexture_.get();
}

void TextureManager::Release()
{
	textureList_.clear();
}

void TextureManager::StaticTextureRelease()
{
	staticTextureList_.clear();
}
