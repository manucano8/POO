// Clase Artículo

#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

#include <set>

class Autor{
public:
    Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) noexcept: nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {};

    const Cadena& nombre() const noexcept { return nombre_; }
    const Cadena& apellidos() const noexcept { return apellidos_; }
    const Cadena& direccion() const noexcept { return direccion_; }

private:
    Cadena nombre_, apellidos_, direccion_;
};

class Articulo{
public:

    typedef std::set<Autor*> Autores;

    Articulo(const Autores& autor, const Cadena& ref,const Cadena& titulo,const Fecha& fpubli,double precio);

    Cadena referencia() const {return ref_;}
    Cadena titulo() const {return titulo_;}
    Fecha f_publi() const {return fpubli_;}

    double precio() const {return precio_;}
    double& precio() {return precio_;}

    const Autores& autores() const {return autor_;}

    class Autores_vacios {};

    virtual void impresion_especifica(std::ostream& os) const = 0;

    virtual ~Articulo() {}

private:
    Autores autor_;
    Cadena ref_;
    Cadena titulo_;
    Fecha fpubli_;
    double precio_;
};

class ArticuloAlmacenable: public Articulo{
public:

    ArticuloAlmacenable(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& f, double p, unsigned stock): Articulo(a, c, t, f, p), stock_(stock) {}

    unsigned stock() const {return stock_;}
    unsigned& stock() {return stock_;}

protected:
    unsigned stock_;
};

class Libro: public ArticuloAlmacenable{
public:
    Libro(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& f, double p, unsigned npag, unsigned s = 0): ArticuloAlmacenable(a, c, t, f, p, s), n_pag_(npag) {}

    unsigned n_pag() const {return n_pag_;}

    void impresion_especifica(std::ostream& os) const;

private:
    unsigned n_pag_;
};

class Cederron: public ArticuloAlmacenable{
public:
    Cederron(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& f, double p, unsigned MB, unsigned s = 0): ArticuloAlmacenable(a, c, t, f, p, s), tam_(MB) {}

    unsigned tam() const {return tam_;}

    void impresion_especifica(std::ostream& os) const;

private:
    unsigned tam_;
};

class LibroDigital: public Articulo{
public:
    LibroDigital(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& f, double p, const Fecha& fexpir): Articulo(a, c, t, f, p), f_expir_(fexpir) {}

    Fecha f_expir() const {return f_expir_;}

    void impresion_especifica(std::ostream& os) const;

private:
    Fecha f_expir_;
};

std::ostream& operator << (std::ostream& os, const Articulo& art);

inline void LibroDigital::impresion_especifica(std::ostream& os) const
{
    os << "A la venta hasta el " << f_expir_ << '.';
}

inline void Libro::impresion_especifica(std::ostream& os) const
{
    os << n_pag_ << " págs., " << stock_ << " unidades.";
}

inline void Cederron::impresion_especifica(std::ostream& os) const
{
    os << tam_ << " MB, " << stock_ << " unidades.";
}

#endif