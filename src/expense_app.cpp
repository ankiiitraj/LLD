#include <expense_app.hpp>
using namespace std;

vector<Expense> expenses;

ExpenseApp::ExpenseApp(string name, vector<User> users)
{
    this->name = name;
    this->id = name + ":random-number-here";
    members = users;
}

void ExpenseApp::showBalance(string userId = "")
{
    ledger.print(userId);
}

void ExpenseApp::addExpense(Expense expense)
{
    ledger.update(expense);
    this->expenses.push_back(expense);
    return;
}