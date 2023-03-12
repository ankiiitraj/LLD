#include <equal_share_expense.hpp>
#include <exact_share_expense.hpp>
#include <expense_app.hpp>
#include <expense.hpp>
#include <ledger_statement.hpp>
#include <ledger.hpp>
#include <user.hpp>
#include <utility.hpp>

using namespace std;

int cnt = 1;

Expense expenseSplitService(
    string payeeUserId,
    double amountPaid,
    string expenseType,
    vector<string> borrowingUserIds,
    vector<double> borrowedAmount = {})
{
    int usersCount = borrowingUserIds.size();
    vector<Share> shares;
    int temp = amountPaid;

    if (expenseType == "EQUAL")
    {
        double eachShareAmount = amountPaid / usersCount;
        for (string userId : borrowingUserIds)
        {
            if (userId != payeeUserId)
                shares.push_back(Share(userId, eachShareAmount, "BORROWED"));
        }
        shares.push_back(Share(payeeUserId, amountPaid - eachShareAmount, "PAID"));
        return EqualShareExpense(payeeUserId, amountPaid, shares);
    }
    else if (expenseType == "EXACT")
    {
        for (int idx; idx < usersCount; ++idx)
        {
            if (borrowingUserIds[idx] == payeeUserId)
            {
                temp -= borrowedAmount[idx];
                continue;
            }
            shares.push_back(Share(borrowingUserIds[idx], borrowedAmount[idx], "BORROWED"));
        }
        shares.push_back(Share(payeeUserId, temp, "PAID"));
        ExactShareExpense expenseToReturn(payeeUserId, amountPaid, shares);
        if (!expenseToReturn.validateShare())
            throw std::invalid_argument("Exact shares don't sum upto the totalAmount.");
        return expenseToReturn;
    }
}

int main()
{
    vector<User> users;
    users.push_back(
        User("ankit", "ankit@exp.com"));
    users.push_back(
        User("prachi", "prachi@exp.com"));
    users.push_back(
        User("abhishek", "abhishek@exp.com"));
    users.push_back(
        User("pankaj", "pankaj@exp.com"));

    ExpenseApp goa("goaaa", users);
    // goa.showBalance();
    goa.showBalance("prachi");

    Expense tickets = expenseSplitService(
        "ankit",
        9999.0,
        "EQUAL",
        {"ankit", "prachi", "pankaj"});
    goa.addExpense(tickets);
    // goa.showBalance();
    goa.showBalance("prachi");

    Expense food = expenseSplitService(
        "prachi",
        6000.0,
        "EQUAL",
        {"ankit", "prachi", "pankaj"});
    goa.addExpense(food);
    // goa.showBalance();
    goa.showBalance("prachi");

    Expense squba = expenseSplitService(
        "pankaj",
        3000.0,
        "EXACT",
        {"prachi", "pankaj"},
        {1500, 1500});
    goa.addExpense(squba);
    // goa.showBalance();
    goa.showBalance("prachi");
}
