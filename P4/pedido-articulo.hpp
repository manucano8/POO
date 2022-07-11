//Clases LineaPedido y Pedido_Articulo

#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include "articulo.hpp"
#include "pedido.hpp"

#include <map>

struct OrdenaArticulos: public std::binary_function <Articulo*, Articulo*, bool>{
    bool operator()(const Articulo* a1, const Articulo* a2) const {return a1->referencia() < a2->referencia();}
};

struct OrdenaPedidos: public std::binary_function <Pedido*, Pedido*, bool>{
    bool operator()(const Pedido* p1, const Pedido* p2) const {return p1->numero() < p2->numero();}
};

class LineaPedido{
public:
    explicit LineaPedido(double precio, unsigned cant = 1);
    double precio_venta() const {return precioventa_;}
    unsigned cantidad() const {return cantidad_;}
private:
    double precioventa_;
    unsigned cantidad_;
};

std::ostream& operator << (std::ostream& output, const LineaPedido& lp);

class Pedido_Articulo{
public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

    
    void pedir(Pedido& p, Articulo& a, double precio, unsigned n = 1);
    void pedir(Articulo& a, Pedido& p, double precio, unsigned n = 1);

    const ItemsPedido& detalle(Pedido& p) const;

    Pedidos ventas(Articulo& a) const;

    void mostrarDetallePedidos(std::ostream& output);
    void mostrarVentasArticulos(std::ostream& output);

private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> Ped_Art_;
    std::map<Articulo*, Pedidos, OrdenaArticulos> Art_Ped_;
};

std::ostream& operator <<(std::ostream& output, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator <<(std::ostream& output, const Pedido_Articulo::Pedidos& p);

#endif