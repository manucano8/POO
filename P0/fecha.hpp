// Clase Fecha

#ifndef FECHA_HPP_
#define FECHA_HPP_

class Fecha{
public:
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
    Fecha (const char* cadena);

    int dia() const {return dia_;}
    int mes() const {return mes_;}
    int anno() const {return anno_;}
    const char* cadena() const;

    class Invalida{
    public:
        Invalida(const char* motivo): motivo_{motivo} {}
        const char* por_que() const {return motivo_;}
    private:
        const char* motivo_;
    };

    Fecha operator ++(int); //Postincremento
    Fecha operator --(int); //Postdecremento
    Fecha operator +(int n) const;
    Fecha operator -(int n) const;
    Fecha& operator +=(int n);
    Fecha& operator -=(int n);
    Fecha& operator ++(); //Preincremento
    Fecha& operator --(); //Predecremento


private:
    int dia_,mes_,anno_;
    void fValida();
    void fSistema(int d, int m, int a);
};

bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);

#endif
