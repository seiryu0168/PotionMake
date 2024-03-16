#pragma once
#include <string>
#include "../Components/Transform.h"

namespace ImageMediationer
{
	Transform Load(const std::string& imagename, const std::string& tabname, int count);
};