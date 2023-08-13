#pragma once

#include <string>

//Defines.
#define BEGIN_SDT_NAMESPACE namespace sdt {

#define END_SDT_NAMESPACE }

#define UNIMPLEMENTED {\
	PLOG(plog::warning) << "Calling an unimplemented function!"; \
	__debugbreak(); \
}

//Statics variables.
constexpr static uint8_t s_majorVersion = 0;
constexpr static uint8_t s_minorVersion = 1;

//Convenience functions.
std::string GetVersionString();