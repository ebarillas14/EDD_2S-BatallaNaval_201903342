#ifndef USER_H
#define USER_H

#include <string>
#include "../../structures/header/linkedList.h"
#include "Articulo.h"
class User
{
private:
    std::string password;
    std::string username;
    int age;
    double coins;
    linkedList<Articulo> skins;
public:
    User();

    void setData(std::string _username, std::string _password, int age, double coins);
    void addSkin(Articulo _skin);
    linkedList<Articulo> getSkins();
    std::string getUsername();
    std::string getPass();
    int getAge();
    double getCoins();
    void setUsername(std::string _username);
    void setAge(int _age);
    void setCoins(double _coins);
    void setPassword(std::string _password);
    bool validatePassword(std::string _password);
};
#endif