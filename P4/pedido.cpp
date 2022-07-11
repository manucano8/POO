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
        if(ArticuloAlmacenable* aa = dynamic_cast<ArticuloAlmacenable*>(i.first))
        {
            if(aa->stock() < i.second)
            {
                const_cast<Usuario::Articulos&>(u.compra()).clear();
                throw Pedido::SinStock(i.first);
            }
        }

        if(LibroDigital* ld = dynamic_cast<LibroDigital*>(i.first))
        {
            if(ld->f_expir() < f){
                u.compra(*i.first, 0);

                if (u.n_articulos() == 0){
                    throw Vacio(u);
                }
            }
        }
    }

    up.asocia (u, *this);
    carro = u.compra();
    
    for(auto j: carro){
        pa.pedir(*this, *j.first, (j.first)->precio(), j.second);
        u.compra(*j.first,0);
        total_ +=   j.second * (j.first)->precio();
        

        if(ArticuloAlmacenable* aa = dynamic_cast<ArticuloAlmacenable*>(j.first)) 
            aa->stock() -= j.second;
    }

    ++numpedidos_;
}

std::ostream& operator <<(std::ostream& output, const Pedido& p){

    output << "Núm. pedido: " << p.numero() << std::endl;
    output << "Fecha: " << p.fecha() << std::endl;
    output << "Pagado con: " << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << std::endl;
    output << "Importe: " << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;

    return output;
}