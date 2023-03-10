#include <expense.hpp>
using namespace std;

Expense::Expense()
{
}

Expense::Expense(string payeeUserId, double amountPaid, vector<Share> shares)
{
    userPaid = payeeUserId;
    date = "12-10-2021";
    title = payeeUserId + "-paid";
    amount = amountPaid;
    description = "random description";
    individualShares = shares;
}