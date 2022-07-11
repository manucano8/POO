// Clases Tarjeta y Número

#include "tarjeta.hpp"
#include <cstring>
#include <iomanip>
#include <algorithm>

bool luhn(const Cadena& num);

bool EsBlanco::operator ()(char c) const {return isspace(c);}

bool EsDigito::operator ()(char c) const {return isdigit(c);}

Numero::Numero(const Cadena& num): numero_(longitud_cadena(num))
{

    if( std::find_if(numero_.begin(), numero_.end(), std::not1(EsDigito())) != numero_.end())
    {
        throw Incorrecto(Razon::DIGITOS);
    }

    if(!luhn(numero_))
    {
        throw Incorrecto(Razon::NO_VALIDO);
    }
}

Cadena Numero::elimina_espacio(const Cadena &cad)
{
    Cadena aux (cad) ;

    std::remove_if(aux.begin(),aux.end()+1,EsBlanco());

    return Cadena(aux.c_str());

}

Cadena Numero::longitud_cadena(const Cadena &cad)
{


    Cadena aux = elimina_espacio(cad);

    if(aux.length() > 19 || aux.length() == 0 || aux.length() < 13 )
    {
        throw Incorrecto(Razon::LONGITUD);
    }

    return aux;
}


bool operator < (const Numero& n1, const Numero& n2){
    return strcmp(n1,n2) < 0;
}

Numero::operator const char*() const
{
    return numero_.c_str();
}

Tarjeta::Tarjetas Tarjeta::tarjetas_;

Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f): numero_(n), titular_(&u), fcaduc_(f)
{  
    if (fcaduc_ < Fecha())
    {
        throw Caducada(fcaduc_);
    }

    if(!tarjetas_.insert(n).second)
    {
        throw Num_duplicado(n);
    }

    const char* aux = n;

    tipo_ = Tipo::Otro;

    if((aux[0] == '3' && aux[1] == '4') || (aux[0] == '3' && aux[1] == '7'))
    {
        tipo_ = Tipo::AmericanExpress;
    }

    if((aux[0] == '3' && aux[1] != '4') || (aux[0] == '3' && aux[1] != '7'))
    {
        tipo_ = Tipo::JCB;
    }

    if((aux[0] == '4'))
    {
        tipo_ = Tipo::VISA;
    }

    if((aux[0] == '5'))
    {
        tipo_ = Tipo::Mastercard;
    }

    if((aux[0] == '6'))
    {
        tipo_ = Tipo::Maestro;
    }

    
    activa_ = true;

    u.es_titular_de(*this);
}


void Tarjeta::anula_titular()
{
    titular_= nullptr;
}

bool Tarjeta::activa(bool act)
{
    activa_ = act;
	return activa_;
}

Tarjeta::~Tarjeta()
{
    if(Usuario* u = const_cast<Usuario*>(titular_)){
        u->no_es_titular_de(*this);
	titular_ = nullptr;
    }

    tarjetas_.erase(numero_);
}

bool operator <(const Tarjeta& t1, const Tarjeta& t2){
    return t1.numero() < t2.numero();
}

std::ostream& operator << (std::ostream& output ,const Tarjeta::Tipo& t)
{

    switch(t)
    {
        case 0: output << "Tipo indeterminado" ; break;
        case 1: output << "VISA" ; break ;
        case 2: output << "Mastercard"; break ;
        case 3: output << "Maestro"; break ;
        case 4: output << "JCB" ; break ;
        case 5: output << "AmericanExpress" ; break ;

        default: output << "Tipo indeterminado"; break ;
    }

    return output ;

}

std::ostream& operator << (std::ostream& output, const Tarjeta& t)
{
	Cadena nom = t.titular()->nombre();
	Cadena apell = t.titular()->apellidos();


	for(size_t i=0; i< nom.length(); i++)
	{
		nom[i] = toupper(nom[i]);
	}

	for(size_t j=0; j< apell.length(); j++)
	{
		apell[j] = toupper(apell[j]);
	}

    output << t.tipo() << "\n" << t.numero() << "\n" << nom << " " << apell << "\n" << "Caduca: " << std::setfill('0') << std::setw(2) << t.caducidad().mes() << "/" << std::setw(2) << (t.caducidad().anno() % 100 ) << "\n" << std::endl;

    return output ;

}
