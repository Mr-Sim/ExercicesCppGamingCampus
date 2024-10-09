#include "include/BankAccount.h"



BaseResponse BankAccount::RequestRetrait(const unsigned int& _amount, const std::string& _code)
{
	bool authorized = Authenticate(_code);
	if (!authorized)
		return BaseResponse();

	bool enougthSolde = TestRetrait(_amount);
	if (!enougthSolde)
		return BaseResponse(authorized, _amount, solde, ExitCode::SoldTooLow);

	solde -= _amount;
	return BaseResponse(authorized, _amount, solde, ExitCode::Success);
}



BaseResponse BankAccount::RequestDepot(const unsigned int& _amount, const std::string& _code)
{
	bool authorized = Authenticate(_code);
	if (!authorized)
		return BaseResponse();

	solde += _amount;
	return BaseResponse(authorized, _amount, solde, ExitCode::Success);
}



BaseResponse BankAccount::RequestSolde(const std::string& _code)
{
	bool authorized = Authenticate(_code);
	if(!authorized)
		return BaseResponse();

	return BaseResponse(authorized, 0, solde);
}

bool BankAccount::TestRetrait(int _amount) {
	return solde - _amount >= 0;
}

bool BankAccount::Authenticate(const std::string _code) {
	return _code == code;
}
