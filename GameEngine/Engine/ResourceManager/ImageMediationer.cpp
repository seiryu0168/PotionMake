#include "ImageMediationer.h"
#include "JsonOperator.h"
#include <filesystem>

namespace
{
	nlohmann::json data;
}

namespace ImageMediationer
{
	Transform Load(const std::string& imagename, const std::string& tabname, int count)
	{
		if (data.empty())
			data = JsonOperator::GetData("Assets\\ImageStatus.json");

		std::filesystem::path path = imagename;
		Transform t;

		t.position_ = { data[tabname][path.filename().string()][count - 2]["Position"]["x"].get<float>(),
		data[tabname][path.filename().string()][count - 2]["Position"]["y"].get<float>(), 0 };

		float scale = data[tabname][path.filename().string()][count - 2]["Scale"].get<float>();
		t.scale_ = { scale, scale, 1 };

		return t;
	}
};