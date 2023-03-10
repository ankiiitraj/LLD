#ifndef __EXPENSE_H_
#define __EXPENSE_H_

#include <utility.hpp>
#include <share.hpp>
using namespace std;

class Expense
{
public:
    string userPaid;
    string date;
    string title;
    string description;
    double amount;
    vector<Share> individualShares;
    Expense();
    Expense(string, double, vector<Share>);
};

#endif