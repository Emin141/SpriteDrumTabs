#pragma once

#include <string>

#define UNIMPLEMENTED {\
	PLOG(plog::warning) << "Calling an unimplemented function!"; \
	__debugbreak(); \
}

//Statics.
constexpr static uint8_t s_majorVersion = 0;
constexpr static uint8_t s_minorVersion = 1;

//Convenience functions.
std::string GetVersionString();