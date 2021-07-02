#include "LML.h"
#include "Test.h"
#include "Student.h"
#include "Answer.h"
#include <map>

void refreshMenu(std::string str);
void refreshMenu(std::shared_ptr<Menu> menu);

void refreshMenu(std::string str)
{
	auto menu = getMenu(str);
	refreshMenu(menu);
}
void refreshMenu(std::shared_ptr<Menu> menu)
{
	int pos = menu->getChosenElementIndex();
	menu->getElements().clear();
	menu->getContentGenerator()(menu);
	if (pos != -1)
		menu->getChosenElementIndex() = pos;
}

std::vector<Test> tests = {
	{
		"Тест по животным", "Биология", 
			{
				{
					"Кто из этих животных кукарекает?",
					{
						{"Петух", true},
						{"Коза", false},
						{"Корова", false}
					}
				},
				{
					"Кто из них относится к кошачьим?",
					{
						{"Кот", true},
						{"Кошка", true},
						{"Собака", false}
					}
				},
				{
					"Один манул.",
					{
						{"Два манула", true},
						{"Три манула", true},
						{"Четыре манула", true},
						{"Пять манулов", true},
						{"Шесть манулов", true},
						{"Семь манулов", true},
						{"Восемь манулов", true},
						{"Девять манулов", true},
						{"Десять манулов", true}
					}
				}
			}
	},
	{
		"Тест по числам", "Математика",
			{
				{
					"1+1?",
					{
						{"2", true},
						{"3", false},
						{"4", false}
					}
				},
				{
					"Выберите цифры.",
					{
						{"1", true},
						{"0", true},
						{"Буква", false}
					}
				},
			}
	}
};

auto sep = MSH(Text, "\n");
std::vector<Answer> lastTestTransactions;
std::map<int, bool> anss;
Test chosenTest = tests[0];

void testChosenMG(std::shared_ptr<Menu> m)
{
	int testIndex = AS(Choice, getMenu("#testChoice")->getElements()[0])->getActiveOption();

	chosenTest = tests[testIndex];
	m->addElement(MSH(Text, "Выбранный тест: " + chosenTest.getName()));
	m->addElement(MSH(Text, "Тема теста: " + chosenTest.getTopic()));

	int optionI = 0;
	for (Question question : chosenTest.getQuestions())
	{
		m->addElement(sep);
		m->addElement(MSH(Text, question.getText()));

	
		for (Option option : question.getOptions())	{
			if (anss.find(optionI) == anss.end())
			{
				anss[optionI] = false;
			}

			auto b = MSH(Button, option.getText() + (anss[optionI]?"(+)":"(-)"), []() {});
			m->addElement(b);
			b->getButtonPressHandler() = [=]() {
				anss[optionI] = !anss[optionI];
				lastTestTransactions.push_back({ {"Евгеньев Евгений Евгеньевич", "ИЭФ", 972303}, question, option, anss[optionI] });
				refreshMenu("#testChosen");
			};
			optionI++;
		}
	}

	m->addElement(sep);

	m->addElement(MSH(Button, "Отменить последнее действие", []() {
		if (!lastTestTransactions.size())
		{
			return;
		}
		Answer lastTransaction = lastTestTransactions[lastTestTransactions.size() - 1];
		lastTestTransactions.pop_back();
		Option o = lastTransaction.getOption();

		int optionI = 0;
		for (Question question : chosenTest.getQuestions())
		{
			for (Option option : question.getOptions()) {
				if (option.getText() == o.getText())
				{
					anss[optionI] = !anss[optionI];
					refreshMenu("#testChosen");
					return;
				}
				optionI++;
			}
		}
	}));

	m->addElement(MSH(Button, "Узнать результат", DialogDecorator::apply([]() {
		std::cout << "Результаты теста: " << std::endl;
		int optionI_ = 0;
		for (Question question : chosenTest.getQuestions())
		{
			int correct = 0;
			int overall = 0;
			for (Option option : question.getOptions())
			{
				if (option.getIsCorrect())
				{
					overall++;
					if (anss[optionI_]) correct++;
				}
				optionI_++;
			}
			std::cout << question.getText() << " Верно отвечено " << correct << " из " << overall << std::endl;
		}
	})));

	m->addElement(MSH(Button, "Назад", []() { MenuManager::removeFromMenuStack(); }));
	m->initChosenElementIndex();
}

void testChoiceMG(std::shared_ptr<Menu> m)
{
	std::vector<std::string> testNames;
	for (auto it : tests)
		testNames.push_back(it.getName());

	newMenu("Прохождение теста", "#testChosen")->getContentGenerator() = testChosenMG;

	MenuStream(m)
		(MSH(Choice, "Выбор теста", testNames))
		(MSH(Button, "Выбрать", []() { 
			lastTestTransactions.clear();
			anss.clear();
			MenuManager::addToMenuStack(getMenu("#testChosen")); 
		}))
		.init();
}


void mainMG(std::shared_ptr<Menu> m)
{
	newMenu("Система тестирования", "#testChoice", 1)->getContentGenerator() = testChoiceMG;
	refreshMenu(getMenu("#testChoice"));

	MenuStream(m)
		(sep)
		(AS(Component, getMenu("#testChoice")))
		(MSH(Button, "Выйти", []() { MenuManager::stopLoops(); }))
		.init();
}

int main()
{
	Console::fixEncoding();
	Console::setMode(Console::standardMode);
	Theme::applyCurrent();

	newMenu("Главное меню", "#main")->getContentGenerator() = mainMG;
	MenuManager::addToMenuStack(getMenu("#main"));

	MenuManager::runLoops();
	Console::sayGoodbye();
}
