#pragma once
#include <string>

class User
{
	// «Пользователь» (ФИО, факультет, номер группы)
private:
	std::string fullName;
	std::string faculty;
	int group;
public:
	User(std::string fullName, std::string faculty, int group) : fullName(fullName), faculty(faculty), group(group) {}
	auto& getFullName() { return fullName; }
	auto& getFaculty() { return faculty; }
	auto& getGroup() { return group; }
};

