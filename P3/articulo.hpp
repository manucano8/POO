// Clase Artículo

#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo{
public:
    Articulo(const Cadena& ref,const Cadena& titulo,const Fecha& fpubli,double precio,unsigned num=0): ref_{ref}, titulo_{titulo}, fpubli_{fpubli}, precio_{precio}, num_{num} {}

    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    unsigned stock() const;
    double& precio();
    unsigned& stock();

private:
    Cadena ref_;
    Cadena titulo_;
    Fecha fpubli_;
    double precio_;
    unsigned num_;
};

inline Cadena Articulo::titulo() const {
    return titulo_;
}

inline Cadena Articulo::referencia() const {
    return ref_;
}

inline Fecha Articulo::f_publi() const {
    return fpubli_;
}

inline double& Articulo::precio() {
    return precio_;
}

inline double Articulo::precio() const {
    return precio_;
}

inline unsigned& Articulo::stock() {
    return num_;
}

inline unsigned Articulo::stock() const {
    return num_;
}

std::ostream& operator << (std::ostream& os, const Articulo& art) ; 

#endif