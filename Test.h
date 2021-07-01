#pragma once
#include <string>
#include <vector>
#include "Question.h"

class Test
{
public:
	Test(std::string name, std::string topic, std::vector<Question> questions) : name(name), topic(topic), questions(questions) {};
	auto& getName() { return name; }
	auto& getTopic() { return topic; }
	auto& getQuestions() { return questions; }
private:
	std::string name;
	std::string topic;
	std::vector<Question> questions;
};

