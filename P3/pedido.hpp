//Clase Pedido

#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "../P1/fecha.hpp"
#include "usuario.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
public:
    
    Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha());

    int numero() const {return num_;}
    const Tarjeta* tarjeta() const {return tarjeta_;}
    Fecha fecha() const {return fecha_;}
    double total() const {return total_;}
    static unsigned n_total_pedidos() {return numpedidos_;}

    class Vacio{
    public:
        Vacio(Usuario& u): u_(&u) {}
        Usuario& usuario() const {return *u_;};
    private:
        Usuario* u_;
    };

    class Impostor{
    public:
        Impostor(Usuario& u): u_(&u) {}
        Usuario& usuario() const {return *u_;};
    private:
        Usuario* u_;
    };

    class SinStock{
    public:
        SinStock(Articulo* a):a_(a) {}
        Articulo& articulo() const { return *a_ ;} ;
    private:
        Articulo* a_;
    };

private:

    int num_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
    static unsigned numpedidos_;
};

std::ostream& operator <<(std::ostream& output, const Pedido& p);

#endif
