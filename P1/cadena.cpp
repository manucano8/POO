//Cano Crespo, Manuel

#include <iostream>
#include "cadena.hpp"
#include <cstring>

Cadena::Cadena(size_t tam, char s): tam_{tam}
{
    
    s_ = new char[tam_+1];

    for(size_t i = 0; i < tam; i++)
    {
        s_[i] = s;
    }

    s_[tam_] = '\0';
}

Cadena::Cadena(const char* cad)
{
    tam_=strlen(cad);

    s_ = new char[tam_+1];

    strcpy(s_,cad);
}

Cadena::Cadena(const Cadena& cad):tam_(cad.tam_)
{
    s_ = new char[cad.tam_+1];

    strcpy(s_,cad.s_);
}

Cadena::Cadena(const Cadena& cad, size_t n, size_t tam):tam_(tam)
{
    if (n > cad.tam_ - 1)
    {
        throw std::out_of_range("Error. Fuera de rango");
    }

    s_ = new char[tam+1];

    size_t i, j = n;

    for (i=0; i < tam_; i++){
        s_[i]=cad[j];
        j++;
    }

    s_[tam_] = '\0';
}

Cadena::Cadena(Cadena&& cad):s_(cad.s_),tam_(cad.tam_)//Constructor de movimiento
{
	cad.s_ = nullptr; 

	cad.tam_ = 0;
}

size_t Cadena::length() const{ return tam_ ; }

//Conversion de tipo Cadena a cadena de caracteres de bajo nivel
const char* Cadena::c_str() const{
    return s_;
}


char Cadena::operator [](size_t n) const{
    return s_[n];
}

char& Cadena::operator [](size_t n){
    return s_[n];
}

char Cadena::at(size_t n) const{
    if(n >= tam_){
        throw std::out_of_range("Error. Fuera de rango");
    }
    return s_[n];
}

char& Cadena::at(size_t n){
    if(n >= tam_){
        throw std::out_of_range("Error. Fuera de rango");
    }
    return s_[n];
}

Cadena Cadena::substr(size_t n,size_t tam) const{
    size_t max=n+tam;
    
    if(max >= length() || n > length() || max < n){
        throw std::out_of_range("Error. Fuera de rango");
    }

    return Cadena(*this,n,tam);
}

Cadena::~Cadena(){
    delete[] s_;
}

Cadena& Cadena::operator =(Cadena&& cad)
{
	
	s_= cad.s_ ; 

	tam_ = cad.tam_ ; 

	cad.s_ = nullptr ; 

	cad.tam_ = 0 ; 

	return *this ; 
}

Cadena& Cadena::operator +=(const Cadena& cad){

    const char* Cadena1 = this->c_str();
    const char* Cadena2 = cad.c_str();
    unsigned tamanno = this->length() + cad.length();
    char* Resultado = new char[tamanno + 1];
    
    unsigned i, j;

    for (i=0; Cadena1[i] != '\0';i++){
        Resultado[i] = Cadena1[i];
    }

    for (j=0; Cadena2[j] != '\0';j++){
        Resultado[i] = Cadena2[j];
        i++;
    }

    this->tam_ = this->length() + cad.length();

    Resultado[tamanno] = '\0';
    this->s_ = Resultado;

    return *this;

}

Cadena operator +(const Cadena& cad1, const Cadena& cad2){
    Cadena aux(cad1);
    aux+=cad2;
    return aux;
}

Cadena& Cadena::operator =(const Cadena& cad){
    if(this != &cad){
        
        this->tam_ = cad.tam_ ; 
	
	    delete[] this->s_ ; 
	
	    this->s_ = new char[ tam_ +1] ; 
	
	    strcpy(this->s_,cad.s_) ;
    }
    
    return *this;
}

Cadena& Cadena::operator =(const char* cad){
    
    this->tam_ = strlen(cad);

    delete[] this->s_;

    this->s_ = new char[ tam_ +1];

    strcpy(this->s_,cad);

    return *this;
}

//Operadores de comparacion

bool operator ==(const Cadena& cad1, const Cadena& cad2)
{
    return strcmp (cad1.c_str(),cad2.c_str()) == 0;
}

bool operator !=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad1 == cad2);
}

bool operator >(const Cadena& cad1, const Cadena& cad2)
{
    return cad2 < cad1;
}

bool operator >=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad1 < cad2);
}

bool operator <(const Cadena& cad1, const Cadena& cad2)
{
    return  strcmp(cad1.c_str(),cad2.c_str()) < 0 ;
}

bool operator <=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad2 < cad1);
}

std::ostream& operator << (std::ostream& os, const Cadena& cad)
{
	os << cad.c_str() ; 

	return os ; 
}

std::istream &operator>>(std::istream& is,Cadena& cad)
{
    char s[33]="";
    is.width(33);
    is >> s;
    cad = s;
    return is;
}
