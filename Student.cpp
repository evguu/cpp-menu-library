#include "Student.h"

std::ostream& operator<<(std::ostream& os, const Student& user)
{
	os << (std::string)user;
	return os;
}