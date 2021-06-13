#pragma once
#include <vector>
#include <string>

class Theme
{
public:
	static void applyNext();
	static void applyCurrent();
private:
	Theme() = delete;
	static std::vector<std::string> themes;
	static int currentIndex;
	static void advanceCurrentIndex();
	static void apply(std::string theme);
	static std::string getCurrent();
};
