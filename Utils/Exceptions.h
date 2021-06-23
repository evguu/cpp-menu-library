#pragma once
#include <exception>
#include <string>

class ManipulativeException
{
public:
	ManipulativeException(std::string what) : _what(what) {};
	std::string what() { return _what; };
private:
	std::string _what;
};
