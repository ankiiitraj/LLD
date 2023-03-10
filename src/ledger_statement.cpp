#include <ledger_statement.hpp>
using namespace std;

LedgerStatement::LedgerStatement(string payeeUserId, string beneficiaryUserId, double amount)
{
    this->payeeUserId = payeeUserId;
    this->beneficiaryUserId = beneficiaryUserId;
    this->amount = amount;
}