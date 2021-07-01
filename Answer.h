#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "Student.h"
#include "Test.h"

class Answer
{
public:
	Answer(Student student, Question question, Option option, bool ans) : student(student), question(question), option(option), ans(ans)
	{
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		date = oss.str();
	};
	auto& getStudent() { return student; }
	auto& getQuestion() { return question; }
	auto& getOption() { return option; }
	auto& getAns() { return ans; }
	auto& getDate() { return date; }
private:
	Student student;
	Question question;
	Option option;
	bool ans;
	std::string date;
};