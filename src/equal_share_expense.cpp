#include <equal_share_expense.hpp>
using namespace std;

EqualShareExpense::EqualShareExpense(string payeeUserId, double amountPaid, vector<Share> shares)
{
    this->userPaid = payeeUserId;
    this->date = "12-10-2021";
    this->title = payeeUserId + "paid";
    this->amount = amountPaid;
    this->description = "random description";
    this->individualShares = shares;
}