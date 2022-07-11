//Clase Usuario_Pedido

#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include "pedido.hpp"
#include "usuario.hpp"

#include <set>
#include <map>

class Usuario_Pedido{
public:
    typedef std::set<Pedido*> Pedidos;

    void asocia(Pedido& p, Usuario& u);
    void asocia(Usuario& u, Pedido& p);

    Pedidos pedidos(Usuario& u) {return usuPed_[&u];}
    Usuario* cliente(Pedido& p) {return pedUsu_[&p];}

private:
    std::map<Usuario*, Pedidos> usuPed_;
    std::map<Pedido*, Usuario*> pedUsu_;

};

inline void Usuario_Pedido::asocia(Pedido &p, Usuario &u)
{
    usuPed_[&u].insert(&p);
    pedUsu_[&p] = &u;
}

inline void Usuario_Pedido::asocia(Usuario &u, Pedido &p)
{
    return asocia(p,u);
}

#endif
