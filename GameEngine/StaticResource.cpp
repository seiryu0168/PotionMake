#include "StaticResource.h"
namespace StaticResource
{
	std::unordered_map<std::string, Image> staticImages_;
	std::unordered_map<std::string, Text> staticTexts_;

	void AddImage(std::string imageName, Image image)
	{
		staticImages_.insert({ imageName,image });
	}

	Image GetImage(std::string imageName)
	{
		assert(staticImages_.find(imageName) != staticImages_.end());

		return staticImages_.find(imageName)->second;
			
	}

	//void StaticImageLoad(std::string imageName, std::string fileName, int cameraNum, int layerNum)
	//{
	//	Image image(cameraNum, layerNum);
	//	if (image.StaticLoad(fileName)==false)
	//		return;
	//	staticImages_.insert({ imageName,image });
	//
	//}

	void AddText(std::string textName, Text text)
	{
		if (staticTexts_.find(textName) != staticTexts_.end())
			return;
		staticTexts_.insert({ textName,text });
	}
	Text GetText(std::string textName)
	{
		assert(staticTexts_.find(textName) != staticTexts_.end());

		return staticTexts_.find(textName)->second;
	}
	void RemoveImage(std::string imageName)
	{
		if (staticImages_.find(imageName) != staticImages_.end())
			return;
		staticImages_.erase(imageName);
	}
	void RemoveText(std::string textName)
	{
		if (staticTexts_.find(textName) != staticTexts_.end())
			return;
		staticTexts_.erase(textName);
	}
	void Draw()
	{
		for (auto&& img : staticImages_)
		{

			if (img.second.IsDraw())
				img.second.Draw();
		}
		for (auto&& txt : staticTexts_)
			txt.second.Draw();

	}
	void Release()
	{
		staticImages_.clear();
		staticTexts_.clear();
	}
}