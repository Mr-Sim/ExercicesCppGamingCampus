#pragma once
#include <string>

enum class ExitCode {
	Success,
	Unauthorized,
	SoldTooLow
};

class BaseResponse {
public:
	BaseResponse(bool _authorized = false, int _diff = 0, int _solde = 0, ExitCode _exitCode = ExitCode::Unauthorized) 
		: authorized(_authorized), solde(_solde), diff(_diff), exitCode(_exitCode) {}
	const bool authorized;
	const int diff;
	const int solde;
	const ExitCode exitCode;
};

class BankAccount{
public:
	BankAccount() = default;

	BaseResponse RequestRetrait(const unsigned int& _amount, const std::string& _code);
	BaseResponse RequestDepot(const unsigned int& _amount, const std::string& _code);
	BaseResponse RequestSolde(const std::string& _code);
private:
	bool Authenticate(std::string _code);
	bool TestRetrait(int _amount);

	int solde;
	std::string code = "1234";
};
