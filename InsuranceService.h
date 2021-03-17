#pragma once
#include <string>
using namespace std;

typedef int Money;
typedef int TrustLevel;

class InsuranceService
{
private:
	string name;
	Money fee;
	Money pay;
	TrustLevel requiredTrustLevel;
public:
	InsuranceService(string name, int fee, int pay, int requiredTrustLevel) : name(name), fee(fee), pay(pay), requiredTrustLevel(requiredTrustLevel) {};
	auto& getName() {return name;}
	auto& getFee() { return fee; }
	auto& getPay() { return pay; }
	auto& getRequiredTrustLevel() { return requiredTrustLevel; }
};
