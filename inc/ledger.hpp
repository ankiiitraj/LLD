#ifndef __LEDGER_H_
#define __LEDGER_H_

#include <utility.hpp>
#include <ledger_statement.hpp>
#include <expense.hpp>
using namespace std;

class Ledger
{
public:
    vector<LedgerStatement> statements;
    vector<LedgerStatement> getLedger(string userId)
    {
        if (userId != "")
        {
            vector<LedgerStatement> filteredLedger;
            for (auto statement : this->statements)
            {
                if (statement.payeeUserId == userId or statement.beneficiaryUserId == userId)
                    filteredLedger.push_back(statement);
            }
            return filteredLedger;
        }
        return this->statements;
    }
    unordered_map<string, double> getUserAmountMap(Expense latestExpense)
    {
        unordered_map<string, double> userAmountMap;

        for (auto statement : this->statements)
        {
            userAmountMap[statement.payeeUserId] -= statement.amount;
            userAmountMap[statement.beneficiaryUserId] += statement.amount;
        }
        for (auto share : latestExpense.individualShares)
        {
            userAmountMap[share.userId] += share.type == "PAID" ? share.amount : -1 * share.amount;
        }
        // printit(userAmountMap);
        return userAmountMap;
    }

    vector<LedgerStatement> getPayeeBeneficiaryMap(unordered_map<string, double> userAmountMap)
    {
        vector<pair<string, double>> whoGets;
        vector<LedgerStatement> statements;
        for (auto itr : userAmountMap)
        {
            if (itr.second > 0)
            {
                whoGets.push_back({itr.first, itr.second});
            }
        }

        int idxUptoPaid = 0;

        for (auto itr : userAmountMap)
        {
            if (itr.second > 0)
                continue;
            double amountTobePaid = abs(itr.second);
            string payeeUserId = itr.first;
            while (amountTobePaid > 0 and idxUptoPaid < whoGets.size())
            {
                if (amountTobePaid >= whoGets[idxUptoPaid].second)
                {
                    statements.push_back(
                        LedgerStatement(
                            payeeUserId,
                            whoGets[idxUptoPaid].first,
                            whoGets[idxUptoPaid].second));
                    whoGets[idxUptoPaid++].second = 0;
                }
                else
                {
                    statements.push_back(
                        LedgerStatement(
                            payeeUserId,
                            whoGets[idxUptoPaid].first,
                            amountTobePaid));
                    whoGets[idxUptoPaid].second -= amountTobePaid;
                    amountTobePaid = 0;
                }
            }
        }

        return statements;
    }

    vector<LedgerStatement> createLedgerStatments(unordered_map<string, double> userAmountMap)
    {
        vector<LedgerStatement> statements = getPayeeBeneficiaryMap(userAmountMap);
        return statements;
    }

    void update(Expense latestExpense)
    {
        unordered_map<string, double> userAmountMap = getUserAmountMap(latestExpense);
        this->statements = createLedgerStatments(userAmountMap);
        return;
    }

    void print(string userId)
    {
        vector<LedgerStatement> statementsToPrint = getLedger(userId);
        cout << "Printing ledger . . .\n";
        if (!statementsToPrint.size())
        {
            cout << "Nothing found\n\n";
            return;
        }
        for (auto statement : statementsToPrint)
        {
            cout << statement.payeeUserId << " owes " << statement.beneficiaryUserId << ": " << abs(statement.amount) << endl;
        }
        cout << endl;
    }
};

#endif