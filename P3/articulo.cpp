// Clase Artículo

#include "articulo.hpp"
#include <ostream>

std::ostream& operator <<(std::ostream& os, const Articulo& art)
{
    os << "[" << art.referencia() << "] \""<< art.titulo() << "," << art.f_publi().anno() <<"." << art.precio() << "€" ;

    return os ;
}