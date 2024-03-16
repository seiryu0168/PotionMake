#include "ModelManager_ECSver.h"

namespace ModelManager_ECSver
{
	std::unordered_map<std::string, std::shared_ptr<Fbx>> models_;

	std::shared_ptr<Fbx> ModelManager_ECSver::Load(const std::string& fileName)
	{
		if (auto itr = models_.find(fileName); itr != models_.end())
		{
			return itr->second;
		}

		std::shared_ptr<Fbx> pFbx = std::make_shared<Fbx>();
		if (FAILED(pFbx->Load(fileName)))
		{
			return nullptr;
		}
		models_.insert({ fileName,pFbx });
		return pFbx;
	}
	void Release()
	{
		models_.clear();
	}
}