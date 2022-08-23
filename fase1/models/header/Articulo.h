#ifndef ARTICULO_H
#define ARTICULO_H

#include <string>

class Articulo
{
private:
public:
    Articulo();
    void setData(int _id, std::string _categoria, double _precio, std::string _nombre, std::string _src);
    int id;
    std::string categoria;
    double precio;
    std::string nombre;
    std::string src;
};
#endif /* ARTICULO_H */