// Clase Cadena

#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{
public:

    //Constructores

    Cadena(size_t tam=0,char s=' '); //Constructor principal
    Cadena(const char* cad); //Constructor a partir de cadena
    Cadena(const Cadena& cad); //Constructor de copia
    Cadena(const Cadena& cad, size_t n, size_t tam); //Constructor de substr

    size_t length() const;

    char operator [](size_t n) const;
    char& operator [](size_t n);
    char at(size_t n) const;
    char& at(size_t n);

    Cadena& operator +=(const Cadena& cad);
    Cadena& operator =(const Cadena& cad);
    Cadena& operator =(const char* cad);

    const char* c_str() const;

    ~Cadena(); //Método destructor

    Cadena substr(size_t n,size_t tam) const;

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


#endif
