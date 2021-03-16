#pragma once
#include "Client.h"
#include "InsuranceService.h"

class notEnoughTrust :exception {};

class Contract
{
private:
	Client client;
	InsuranceService insuranceService;
public:
	Contract(Client client, InsuranceService insuranceService) : client(client), insuranceService(insuranceService)
	{
		if (client.getTrustLevel() < insuranceService.getRequiredTrustLevel()) throw notEnoughTrust();
	};
	auto& getClient() { return client; }
	auto& getInsuranceService() { return insuranceService; }
};
