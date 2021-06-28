#pragma once
#include <string>
#include <vector>

class Test
{
	// «Тест» (название теста, тема теста, перечень вопросов, перечень полученных ответов)
private:
	std::string name;
	std::string topic;
	std::vector<std::string> questions;
	std::vector<std::string> answers;
public:
	Test(std::string name, std::string topic, std::vector<std::string> questions) :
		name(name), topic(topic), questions(questions), answers({}) {}
	auto& getName() { return name; }
	auto& getTopic() { return topic; }
	auto& getQuestions() { return questions; }
	auto& getAnswers() { return answers; }
};

