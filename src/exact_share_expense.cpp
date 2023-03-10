#include <exact_share_expense.hpp>
using namespace std;

ExactShareExpense::ExactShareExpense(string payeeUserId, double amountPaid, vector<Share> shares)
{
    this->userPaid = payeeUserId;
    this->date = "12-10-2021";
    this->title = payeeUserId + "paid";
    this->amount = amountPaid;
    this->description = "random description";
    this->individualShares = shares;
}

bool ExactShareExpense::validateShare()
{
    double sumOfShares = 0;
    for (const auto share : this->individualShares)
    {
        sumOfShares += share.type == "PAID" ? -share.amount : share.amount;
    }

    return sumOfShares == 0;
}