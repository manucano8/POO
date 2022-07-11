// Clase Artículo

#include "articulo.hpp"
#include <ostream>
#include <iomanip>

Articulo::Articulo(const Autores& autor, const Cadena& ref, const Cadena& titulo,const Fecha& fpubli, double precio): autor_(autor), ref_{ref}, titulo_{titulo}, fpubli_{fpubli}, precio_{precio} {

    if(autor_.empty())
        throw Autores_vacios();
}

std::ostream& operator <<(std::ostream& os, const Articulo& art)
{
    os << "[" << std::setw(3) << std::setfill('0') << art.referencia() << "] \""<< art.titulo() << "\", de ";

    auto autor = art.autores().begin();

    os << (*autor)->apellidos();

    for(++autor; autor != art.autores().end(); ++autor){
        os << ", " << (*autor)->apellidos();
    }
    
    os << ". ";

    os << art.f_publi().anno() <<". " << std::fixed << std::setprecision(2) << art.precio() << " €" << std::endl;

    os << "\t";

    art.impresion_especifica(os);

    return os ;
}
