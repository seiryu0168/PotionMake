#include "ImageManager_ECSver.h"
namespace ImageManager_ECSver
{

		std::unordered_map<std::string, std::shared_ptr<Sprite>> images_;
		std::unordered_map<std::string, std::shared_ptr<Sprite>> staticImages_;
    std::shared_ptr<Sprite> Load(const std::string& fileName)
    {	
			if (auto itr = images_.find(fileName); itr != images_.end())
			{
				return itr->second;
			}

			std::shared_ptr<Sprite> image = std::make_shared<Sprite>();
			if (FAILED(image->Load(fileName)))
			{
				return nullptr;
			}
			
			images_.insert({ fileName,image });


			return image;
    }

	std::shared_ptr<Sprite> StaticLoad(const std::string& fileName)
	{
		if (auto itr = staticImages_.find(fileName); itr != staticImages_.end())
		{
			return itr->second;
		}

		std::shared_ptr<Sprite> image = std::make_shared<Sprite>();
		if (FAILED(image->StaticLoad(fileName)))
		{
			return nullptr;
		}

		staticImages_.insert({ fileName,image });


		return image;
	}
	void Release()
	{
		images_.clear();
	}
	void StaticImageRelease()
	{
		staticImages_.clear();
	}
}
