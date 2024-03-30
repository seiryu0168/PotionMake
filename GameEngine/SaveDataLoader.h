#pragma once
#include"Engine/ResourceManager/json.hpp"
class SaveDataLoader
{
	nlohmann::json jsonFile_;
public:
	SaveDataLoader();
	~SaveDataLoader();
	void Init();
	void Load(std::string fileName);
};

