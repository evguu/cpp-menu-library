#pragma once
#include <string>
using namespace std;

typedef int TrustLevel;

class Client
{
private:
	string name;
	TrustLevel trustLevel;
public:
	Client(string name, int trustLevel) : name(name), trustLevel(trustLevel) {};
	auto& getName() { return name; }
	auto& getTrustLevel() { return trustLevel; }
};
