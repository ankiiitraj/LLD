#ifndef __EXPENSE_APP_H_
#define __EXPENSE_APP_H_

#include <utility.hpp>
#include <expense.hpp>
#include <user.hpp>
#include <ledger.hpp>
using namespace std;

class ExpenseApp
{
public:
    vector<Expense> expenses;
    ExpenseApp(string, vector<User>);
    void showBalance(string);
    void addExpense(Expense);

private:
    string id;
    string name;
    vector<User> members;
    Ledger ledger;
};

#endif