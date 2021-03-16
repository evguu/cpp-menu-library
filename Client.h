#pragma once
#include <string>
using namespace std;

class Client
{
private:
	string name;
	int trustLevel;
public:
	Client(string name, int trustLevel) : name(name), trustLevel(trustLevel) {};
	auto& getName() { return name; }
	auto& getTrustLevel() { return trustLevel; }
};
