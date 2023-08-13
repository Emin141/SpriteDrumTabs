#pragma once

#include "Globals.h"

#include <string>

BEGIN_SDT_NAMESPACE
class DrumkitPiece
{
public:
	using Name = std::string;

	void SetName(const Name& value);
	const Name& GetName() const;

private:
	Name _name;
	
};
END_SDT_NAMESPACE