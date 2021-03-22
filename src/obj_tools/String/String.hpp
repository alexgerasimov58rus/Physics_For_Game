#pragma once

#include "../tools_exp.hpp"
#include <vector>
#include <string>

namespace obj_tools {

	struct OBJ_TOOLS_EXPORT String
	{
		static std::vector<std::string> split(std::string, char separator);
	};
};