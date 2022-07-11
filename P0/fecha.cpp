#include <iostream>
#include "fecha.hpp"
#include <ctime>

using namespace std;

//Constructor
Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno} {
    fSistema(dia, mes, anno);
    fValida();
}

Fecha::Fecha (const char* cadena){
    int dia,mes,anno;

    if(sscanf(cadena, "%d/%d/%d", &dia, &mes, &anno) != 3)
        throw Invalida("Fecha invalida");
    else{
        
        dia_ = dia;
        mes_ = mes;
        anno_ = anno;

        fSistema(dia,mes,anno);
        fValida();
    }
}

void Fecha::fSistema(int d, int m, int a){
    std::time_t tc = std::time(nullptr);
    std::tm* td = std::localtime(&tc);

    if(a == 0)
    {
        anno_ = td->tm_year + 1900;
    }

    if(m == 0)
    {
        mes_ = td->tm_mon + 1;
    }

    if(d == 0)
    {
        dia_ = td->tm_mday;
    }
}

void Fecha::fValida(){
    const int dias [] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if(anno_ > Fecha::AnnoMaximo ||  anno_ < Fecha::AnnoMinimo){
        throw Invalida("Anno invalido");
    }

    if(mes_ > 12 || mes_ < 1)
    {
        throw Invalida("Mes invalido");
    }

    if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)){
        if(dia_ > 29 || dia_ < 1){
            throw Invalida("Dia invalido");
        }
    }
    else{
        if (dia_ > dias[mes_-1] || dia_ < 1){
            throw Invalida("Dia invalido");
        }
    }
}

const char* Fecha::cadena() const{
    
    setlocale(LC_ALL,"");
    
    const char* dias[] = {"domingo","lunes","martes","miércoles","jueves","viernes","sábado"};

    const char* meses[] = {".","enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};

    static char resultado[40];

    tm f = {0};

    f.tm_mday = dia_;
    f.tm_mon = mes_ - 1;
    f.tm_year = anno_ - 1900;

    mktime(&f);
    snprintf(resultado,sizeof(resultado), "%s %d de %s de %d", dias[f.tm_wday], f.tm_mday, meses[f.tm_mon+1], f.tm_year + 1900);

    return resultado;
}

//Operadores de suma, resta, incremento, decremento y asignación

Fecha& Fecha::operator +=(int n){
    tm faux={};

    faux.tm_mday = dia() + n;
    faux.tm_mon = mes() - 1;
    faux.tm_year = anno() - 1900;

    mktime(&faux);

    anno_ = faux.tm_year + 1900;
    mes_ = faux.tm_mon + 1;
    dia_ = faux.tm_mday;
    fValida();

    return *this;


}

Fecha& Fecha::operator -=(int n){
    return *this += -n;
}

Fecha Fecha::operator +(int n) const{
    Fecha f = *this;
    f += n;
    return f;
}

Fecha Fecha::operator -(int n) const{
    Fecha f = *this;
    f += -n;
    return f;
}

Fecha Fecha::operator ++(int){
    Fecha f = *this;
    *this += 1;
    return f;
}

Fecha Fecha::operator --(int){
    Fecha f = *this;
    *this += -1;
    return f;
}

Fecha& Fecha::operator ++(){
    return *this += 1;
}

Fecha& Fecha::operator --(){
    return *this += -1;
}

//Operadores de comparación

bool operator ==(const Fecha& f1, const Fecha& f2){
    return (f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() == f2.dia());
}

bool operator <(const Fecha& f1, const Fecha& f2){
    if (f1.anno() < f2.anno()){return true;}
    else if (f1.anno() == f2.anno() && f1.mes() < f2.mes()){return true;}
    else if (f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() < f2.dia()){return true;}
    else return false;
}

bool operator !=(const Fecha& f1, const Fecha& f2){
    return !(f1 == f2);
}

bool operator >(const Fecha& f1, const Fecha& f2){
    return (f2 < f1);
}

bool operator >=(const Fecha& f1, const Fecha& f2){
    return !(f1 < f2);
}

bool operator <=(const Fecha& f1, const Fecha& f2){
    return !(f2 < f1);
}
