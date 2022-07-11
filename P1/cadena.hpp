// Cano Crespo, Manuel

#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <iterator>
#include <string>

class Cadena{
public:

    //Constructores

    Cadena(size_t tam=0,char s=' '); //Constructor principal
    Cadena(const char* cad); //Constructor a partir de cadena
    Cadena(const Cadena& cad); //Constructor de copia
    Cadena(const Cadena& cad, size_t n, size_t tam); //Constructor de substr
    Cadena(Cadena&& cad);  //Constructor de movimiento

    size_t length() const;

    char operator [](size_t n) const;
    char& operator [](size_t n);
    char at(size_t n) const;
    char& at(size_t n);

    Cadena& operator =(Cadena&& cad); //  Asignacion en movimiento
    Cadena& operator +=(const Cadena& cad);
    Cadena& operator =(const Cadena& cad);
    Cadena& operator =(const char* cad);

    const char* c_str() const;

    ~Cadena(); //Método destructor

    Cadena substr(size_t n,size_t tam) const;

    //Iteradores (Tipos dentro de Cadena)

    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    //Iteradores (Funciones dentro de Cadena)

    iterator begin() { return s_;}
	const_iterator begin() const { return cbegin();}
	const_iterator cbegin() const { return s_;}
	reverse_iterator rbegin() { return reverse_iterator(end());}
	const_reverse_iterator rbegin() const {return crbegin();}
	const_reverse_iterator crbegin() const { return const_reverse_iterator(end());}

    iterator end() { return s_ + tam_ ;}
	const_iterator end() const {return cend();}
	const_iterator cend() const { return s_ + tam_ ;}
	reverse_iterator rend() { return reverse_iterator(begin());}
	const_reverse_iterator rend() const { return crend();}
	const_reverse_iterator crend() const { return const_reverse_iterator(begin());}


private:
    char* s_;
    size_t tam_;
};

//Operador de suma de dos cadenas
Cadena operator +(const Cadena& cad1, const Cadena& cad2);

//Operadores de comparacion

bool operator ==(const Cadena& cad1, const Cadena& cad2);
bool operator !=(const Cadena& cad1, const Cadena& cad2);
bool operator >(const Cadena& cad1, const Cadena& cad2);
bool operator >=(const Cadena& cad1, const Cadena& cad2);
bool operator <(const Cadena& cad1, const Cadena& cad2);
bool operator <=(const Cadena& cad1, const Cadena& cad2);

std::ostream& operator << (std::ostream& os, const Cadena& cad) ; 
std::istream& operator >> (std::istream& is, Cadena& cad) ;

namespace std { 
  template <>
  struct hash<Cadena> {
    size_t operator() (const Cadena& cad) const
    {
      hash<string> hs; // Creamos un objeto hash de string
      const char* p = cad.c_str(); // Obtenemos la cadena de la Cadena
      string s(p); // Creamos un string desde una cadena
      size_t res = hs(s); // El hash del string. Como hs.operator()(s);
      return res; // Devolvemos el hash del string
    }
  };
}
#endif
