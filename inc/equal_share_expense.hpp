#ifndef __EQUAL_SHARE_EXPENSE_H_
#define __EQUAL_SHARE_EXPENSE_H_

#include <expense.hpp>
#include <share.hpp>
using namespace std;

class EqualShareExpense : public Expense
{
public:
    EqualShareExpense(string, double, vector<Share>);
};

#endif