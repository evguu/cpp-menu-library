#pragma once
#include <string>
using namespace std;

class InsuranceService
{
private:
	string name;
	int fee;
	int pay;
	int requiredTrustLevel;
public:
	InsuranceService(string name, int fee, int pay, int requiredTrustLevel) : name(name), fee(fee), pay(pay), requiredTrustLevel(requiredTrustLevel) {};
	auto& getName() {return name;}
	auto& getFee() { return fee; }
	auto& getPay() { return pay; }
	auto& getRequiredTrustLevel() { return requiredTrustLevel; }
};
