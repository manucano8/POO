// Clases Usuario y Clave

#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include "articulo.hpp"

#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>

class Tarjeta;

class Clave{
public:
    Clave(const char* cad);

    enum Razon{CORTA, ERROR_CRYPT};

    class Incorrecta{
    public:
        Incorrecta(const Razon r): fallo_(r) {}
        Razon razon() const {return fallo_; }
    private:
        Razon fallo_;
    };

    const Cadena& clave() const;
    bool verifica(const char* cad) const;

private:
    Cadena contrasenna_;
};

inline const Cadena& Clave::clave() const {
    return contrasenna_;
}

class Numero;
class Tarjeta;

class Usuario{
public:

    typedef std::unordered_set<Cadena> Usuarios;
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apellidos,const Cadena& direccion,const Clave& contrasenna);

    Usuario& operator =(const Usuario& u) = delete;
    Usuario(const Usuario& u) = delete;

    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena& i): ident_(i){}
        const Cadena idd() const {return ident_;};
    private:
        Cadena ident_;
    };

    Cadena id() const {return id_;};
    Cadena nombre() const {return nombre_;};
    Cadena apellidos() const {return apellidos_;};
    Cadena direccion() const {return direccion_;};

    void es_titular_de(Tarjeta& t);
    void no_es_titular_de(Tarjeta& t);
    void compra(Articulo& a, unsigned cantidad = 1);

    const Tarjetas& tarjetas() const {return tarjetas_;};
    const Articulos& compra() const {return articulos_;};

    ~Usuario();

    size_t n_articulos() const {return articulos_.size();}

    friend std::ostream& operator <<(std::ostream& os, const Usuario& u);
    
private:
    Cadena id_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave contrasenna_;
    Tarjetas tarjetas_;
    Articulos articulos_;
    static Usuarios usuarios_;
    
};

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u);



#endif
