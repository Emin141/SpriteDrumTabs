#include "DrumkitPiece.h"

void sdt::DrumkitPiece::SetName(const Name& value)
{
	_name = value;
}

const sdt::DrumkitPiece::Name& sdt::DrumkitPiece::GetName() const
{
	return _name;
}
