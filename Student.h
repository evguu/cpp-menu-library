#pragma once
#include <string>
#include <sstream>
#include <iostream>

class Student
{
private:
	std::string fullName;
	std::string faculty;
	int group;
public:
	Student(std::string fullName, std::string faculty, int group) : fullName(fullName), faculty(faculty), group(group) {}
	auto& getFullName() { return fullName; }
	auto& getFaculty() { return faculty; }
	auto& getGroup() { return group; }
	operator std::string() const
	{
		std::stringstream ss;
		ss << "Студент " << fullName <<
			" факультета " << faculty <<
			" группы " << group;
		return ss.str(); 
	};
	friend std::ostream& operator<<(std::ostream& os, const Student& user);
};
