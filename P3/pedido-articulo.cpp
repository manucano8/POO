//Clases LineaPedido y Pedido_Articulo

#include "pedido-articulo.hpp"

#include <iomanip>

LineaPedido::LineaPedido(double precio, unsigned cant): precioventa_(precio), cantidad_(cant){}   

std::ostream& operator << (std::ostream& output, const LineaPedido& lp){

    output << std::fixed << std::setprecision(2) << lp.precio_venta() << " €" << '\t' << lp.cantidad();

    return output;
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned n)
{
    Art_Ped_[&a].insert(std::make_pair(&p,LineaPedido(precio,n)));
    Ped_Art_[&p].insert(std::make_pair(&a,LineaPedido(precio,n)));
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p,double precio, unsigned n)
{
    pedir(p,a,precio,n);
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p) const{
    return Ped_Art_.at(&p);
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a) const{
    auto i=Art_Ped_.find(&a);
    if(i != Art_Ped_.end()){
        return i->second;
    }
    else{
        return Pedidos();
    }
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& output)
{
    for(auto it = Art_Ped_.begin(); it != Art_Ped_.end(); it++)
    {
        output << "Ventas de " << "[" << (it->first)->referencia() << "] " ;
        output << "\"" << it->first->titulo() << "\"" ;
        output << ventas(*it->first) << std::endl ;
    }
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream& output)
{
    double precio = 0;

    for(auto it = Ped_Art_.begin(); it != Ped_Art_.end() ; it++)
    {

        output << "Pedido núm." << (it->first)->numero() << "\t" ;
        output << "Cliente: " << (it->first)->tarjeta()->titular()->nombre() << "\t";
        output << "Fecha: " << (it->first)->fecha() << detalle(*it->first) ;

        precio = precio + (it->first)->total() ;
    }

    output << std::fixed ;
    output << "TOTAL VENTAS: " << std::setprecision(2) << precio << " €" << std::endl ;
}

std::ostream& operator <<(std::ostream& output,const Pedido_Articulo::ItemsPedido& ip)
{

    double precio = 0;

    output << "\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << "PVP \t Cant.\t Articulo\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

    for(auto it = ip.begin(); it != ip.end() ; it++)
    {

        output << (it->second).precio_venta() << "€\t" ;
        output << (it->second).cantidad() << "\t" ;
        output << "[ "<< (it->first)->referencia() << "]\t";
        output << "\"" << (it->first)->titulo() << "\"" << std::endl;

        precio = precio + (it->second).cantidad() * (it->second).precio_venta() ;
    }

    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << std::fixed ;
    output << std::setprecision(2) << precio << " €" << std::endl ;

    return output ;
}

std::ostream& operator <<(std::ostream& output, const Pedido_Articulo::Pedidos& pa)
{

    double precio = 0;
    unsigned t = 0  ;

    output << "\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << "PVP \t Cant.\t Fecha venta\n" ;
    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

    for(auto it = pa.begin(); it != pa.end() ; it++)
    {

        output << " " << (it->second).precio_venta() << " €\t" ;
        output << (it->second).cantidad() << "\t" ;
        output << (it->first)->fecha() << std::endl ;

        precio = precio + (it->second).cantidad() * (it->second).precio_venta() ;
        t += (it->second).cantidad() ;
    }


    output << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    output << std::fixed ;
    output << std::setprecision(2) << precio << " €\t" << t << std::endl ;

    return output ;

}

