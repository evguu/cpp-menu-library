#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "Student.h"

class Answer
{
private:
	std::string date;
	Student user;
public:
	Answer(Student user) : user(user) 
	{
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		date = oss.str();
	}
	auto& getDate() { return date; }
	auto& getUser() { return user; }

};
