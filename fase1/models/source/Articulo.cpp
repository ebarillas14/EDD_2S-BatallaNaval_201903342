#include <string>
#include <iostream>
#include "../header/Articulo.h"
// CONSTRUCTOR
Articulo::Articulo()
{
}

void Articulo::setData(int _id, std::string _categoria, double _precio, std::string _nombre, std::string _src)
{
    id = _id;
    categoria = _categoria;
    precio = _precio;
    nombre = _nombre;
    src = _src;
}
