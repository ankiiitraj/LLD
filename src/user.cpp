#include <user.hpp>
using namespace std;

User::User(string name, string email)
{
    this->name = name;
    this->email = email;
    this->userId = name;
}