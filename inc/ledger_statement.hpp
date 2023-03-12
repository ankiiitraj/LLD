#ifndef __LEDGER_STATEMENT_H_
#define __LEDGER_STATEMENT_H_

#include <utility.hpp>
using namespace std;

class LedgerStatement
{
public:
    string payeeUserId;
    string beneficiaryUserId;
    double amount;
    LedgerStatement(string, string, double);
};

#endif