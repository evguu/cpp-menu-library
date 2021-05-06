#pragma once
#include <vector>
#include <string>

class Theme
{
private:
	Theme() = delete;
	static std::vector<std::string> themes;
	static int currentIndex;
	static void advanceCurrentIndex();
	static void apply(std::string theme);
	static std::string getCurrent();
public:
	static void applyNext();
	static void applyCurrent();
};
