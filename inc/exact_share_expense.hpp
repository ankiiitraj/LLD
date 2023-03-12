#ifndef __EXACT_SHARE_EXPENSE_H_
#define __EXACT_SHARE_EXPENSE_H_

#include <expense.hpp>
#include <share.hpp>
using namespace std;

class ExactShareExpense : public Expense
{
public:
    ExactShareExpense(string, double, vector<Share>);
    bool validateShare();
};

#endif