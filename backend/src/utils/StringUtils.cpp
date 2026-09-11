#include "utils/StringUtils.hpp"

#include <cctype>

using namespace std;


//Convierte texto a minuscula
string StringUtils::toLower(const string& text){
    string lowerText = text;

    for (char& character : lowerText){
        character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
    }

    return lowerText;
}


//Convierte texto a mayuscula
string StringUtils::toUpper(const string& text){
    string upperText = text;

    for (char& character : upperText){
        character = static_cast<char>(toupper(static_cast<unsigned char>(character)));
    }

    return upperText;
}


//Compara dos textos ignorando mayusculas
bool StringUtils::equalsIgnoreCase(const string& firstText, const string& secondText){
    return toLower(firstText) == toLower(secondText);
}


//Quita espacios al inicio y final
string StringUtils::trim(const string& text){
    size_t start = 0;
    size_t end = text.size();

    //busca primer caracter que no sea espacio
    while (start < text.size() && (text[start] == ' ' || text[start] == '\t' || text[start] == '\r' || text[start] == '\n')){
        start++;
    }

    //busca ultimo caracter que no sea espacio
    while (end > start && (text[end - 1] == ' ' || text[end - 1] == '\t' || text[end - 1] == '\r' || text[end - 1] == '\n')){
        end--;
    }

    return text.substr(start, end - start);
}


//Separa texto usando un delimitador
vector<string> StringUtils::split(const string& text, char delimiter){
    vector<string> parts;
    string currentPart;

    //recorre el texto y forma cada parte
    for (char character : text){
        if (character == delimiter){
            parts.push_back(currentPart);
            currentPart = "";
            continue;
        }

        currentPart += character;
    }

    //guarda la ultima parte
    parts.push_back(currentPart);

    return parts;
}


//Verifica si el texto esta vacio
bool StringUtils::isEmpty(const string& text){
    return trim(text).empty();
}