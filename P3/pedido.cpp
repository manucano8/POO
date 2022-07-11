//Clase pedido

#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

#include <iomanip>

unsigned Pedido::numpedidos_ = 0;

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f): num_(numpedidos_ + 1), tarjeta_(&t), fecha_(f), total_(0){

    if(t.caducidad() < f){
        throw Tarjeta::Caducada(t.caducidad());
    }

    if(u.n_articulos() == 0){
        throw Vacio(u);
    }

    if(t.titular() != &u){
        throw Impostor(u);
    }

    if(t.activa() != true){
        throw Tarjeta::Desactivada();
    }

    auto carro = u.compra(); //carro contendrá el carrito de compra del usuario

    for(auto i: carro)
    {
        if((i.first)->stock() < (i.second)) //si el stock del artículo es menor que la cantidad del artículo en el carrito
        {
            const_cast<Usuario::Articulos&>(u.compra()).clear(); //vacia el carrito
            throw SinStock(i.first);
        }
    }

    for(auto i: carro){
        unsigned cant = (i.second);
        Articulo* a = (i.first);
        double precio = a->precio();
        a->stock() -= cant;

        pa.pedir(*this, *a, precio, cant);
        total_ += precio * cant;
        u.compra(*a, 0);
    }

    up.asocia (u, *this);

    ++numpedidos_;

}

std::ostream& operator <<(std::ostream& output, const Pedido& p){

    output << "Núm. pedido: " << p.numero() << std::endl;
    output << "Fecha: " << p.fecha() << std::endl;
    output << "Pagado con: " << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << std::endl;
    output << "Importe: " << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;

    return output;
}
