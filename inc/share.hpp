#ifndef __SHARE_H_
#define __SHARE_H_

#include <utility.hpp>
using namespace std;

class Share
{
public:
    string userId;
    double amount;
    string type;

    Share(string, double, string);
};

#endif