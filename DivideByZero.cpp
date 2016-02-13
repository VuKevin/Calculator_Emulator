#include "DivideByZero.h"

namespace VuKevin
{
	DivideByZero::DivideByZero(const std::string & msg)
		: std::logic_error("Division by zero attempted.\n")
	{}

	const char* DivideByZero::what() const
	{
		return "Division by zero attempted.\n";
	}
}
