#include <share.hpp>
using namespace std;

Share::Share(string userId, double amount, string type)
{
    this->userId = userId;
    this->amount = amount;
    this->type = type;
}