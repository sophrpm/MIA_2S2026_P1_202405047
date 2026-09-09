#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>

using namespace std;


//Utilidades para trabajar con texto
class StringUtils {
public:

    //Convierte texto a minuscula
    static string toLower(const string& text);

    //Convierte texto a mayuscula
    static string toUpper(const string& text);

    //Compara dos textos ignorando mayusculas
    static bool equalsIgnoreCase(const string& firstText, const string& secondText);

    //Quita espacios al inicio y final
    static string trim(const string& text);

    //Separa texto usando un delimitador
    static vector<string> split(const string& text, char delimiter);

    //Verifica si el texto esta vacio
    static bool isEmpty(const string& text);
};


#endif