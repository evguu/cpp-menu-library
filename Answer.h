#pragma once
#include <string>
#include "User.h"

class Answer
{
	// «Ответ»(дата выполнения теста, ФИО выполнившего тест).
private:
	std::string date;
	User user;
public:
	Answer(std::string date, User user) : date(date), user(user) {}
	auto& getDate() { return date; }
	auto& getUser() { return user; }

};

