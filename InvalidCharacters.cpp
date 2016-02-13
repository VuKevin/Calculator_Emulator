#include "InvalidCharacters.h"


namespace VuKevin
{
	InvalidCharacter::InvalidCharacter(const std::string & msg)
		: std::logic_error("Invalid characters found.")
	{}
}
