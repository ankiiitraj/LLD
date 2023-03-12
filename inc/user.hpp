#ifndef __USER_H_
#define __USER_H_

#include <utility.hpp>
using namespace std;

class User
{
public:
    string name;
    string email;
    string userId;
    double balance = 0.0;

    User(string, string);
};

#endif