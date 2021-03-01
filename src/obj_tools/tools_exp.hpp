
#pragma once

#ifdef OBJ_TOOLS_LIB
# define OBJ_TOOLS_EXPORT __declspec(dllexport)
#else
# define OBJ_TOOLS_EXPORT __declspec(dllimport)
#endif
