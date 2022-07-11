// Clases Usuario y Clave

#include "usuario.hpp"
#include <unistd.h>
#include <cstring>
#include <iomanip>

Clave::Clave(const char* cad)
{
    const char* alfabeto = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char* sal = new char [2];

    if(strlen(cad) < 5)
    {
        throw Incorrecta(Razon::CORTA);
    }

    sal[0] = alfabeto[rand() % 64];
    sal[1] = alfabeto[rand() % 64];

    if(crypt(cad,sal) == NULL)
    {
        throw Incorrecta(Razon::ERROR_CRYPT);
    }

    contrasenna_ = crypt(cad,sal);

    delete[] sal;
}

bool Clave::verifica(const char* cad) const
{
    return std::strcmp(crypt(cad, contrasenna_.c_str()), contrasenna_.c_str()) == 0;
}

Usuario::Usuarios Usuario::usuarios_;

Usuario:: Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apellidos,const Cadena& direccion,const Clave& contrasenna):
id_(id), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), contrasenna_(contrasenna)
{
    if(!usuarios_.insert(id).second)
    {
        throw Id_duplicado(id_);
    }
}

void Usuario::compra(Articulo &a, unsigned cantidad)
{
    if(cantidad != 0)
    {
        articulos_[&a] = cantidad;
    }else{
        articulos_.erase(&a);
    }
}

void Usuario::es_titular_de(Tarjeta &t)
{
    if(this == t.titular())
    {
        tarjetas_.insert(std::make_pair(t.numero(), &t));
    }
}

void Usuario::no_es_titular_de(Tarjeta &t)
{
    t.anula_titular();
    tarjetas_.erase(t.numero());
}

std::ostream& operator <<(std::ostream& output, const Usuario& u)
{
    output << u.id_ << "[" << u.contrasenna_.clave().c_str() << "]" << u.nombre_ << u.apellidos_ << "\n" << u.direccion_ << std::endl;
    output <<"Tarjetas:";
    for(auto i = u.tarjetas().begin(); i != u.tarjetas().end(); i++)
    {
        output << *i->second << std::endl;
    }

    return output;
}

std::ostream& mostrar_carro(std::ostream& output, const Usuario& u)
{
    output << "Carrito de compra de " << u.id() << " [Artículos: "<< u.n_articulos() << "]" << "\n" << "Cant.Artículo"<< std::endl << std::setw(95) << std::setfill('=') << '\n' << std::setfill(' ');

    int num_art = u.n_articulos() ;

    while( num_art > 0 )
    {
        for(auto i = u.compra().begin(); i != u.compra().end(); i++)
        {
            output << std::setw(4) << i->second << "    " << " [" << (*i->first).referencia() << "] " << "\"" << (*i->first).titulo() << "\", " << (*i->first).f_publi().anno() << ". " << std::fixed << std::setprecision(2) << (*i->first).precio() << " €" << std::endl;

            --num_art;
        }
    }

    return output;
}

Usuario::~Usuario()
{
    for(auto i = tarjetas_.begin(); i != tarjetas_.end(); i++)
    {
        i->second->anula_titular();
    }

    usuarios_.erase(id_);
}
