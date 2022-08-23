#include <string>
#include <iostream>
#include "../header/User.h"
#include "../../modules/sha256.h"
// CONSTRUCTOR
User::User()
{
}

void User::setData(std::string _username, std::string _password, int _age, double _coins)
{
    coins = _coins;
    username = _username;
    password = _password;
    age = _age;
}

std::string User::getUsername()
{
    return username;
}

std::string User::getPass()
{
    return password;
}

double User::getCoins()
{
    return coins;
}
bool User::validatePassword(std::string _password)
{
    return (password == _password);
}

void User::setUsername(std::string _username)
{
    username = _username;
}
void User::setAge(int _age)
{
    age = _age;
}
void User::setCoins(double _coins)
{
    coins = _coins;
}
void User::setPassword(std::string _password)
{
    password = _password;
}