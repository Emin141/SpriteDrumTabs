#include "Globals.h"

std::string GetVersionString()
{
	return std::to_string(s_majorVersion) + "." + std::to_string(s_minorVersion);
}
