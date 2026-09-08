#ifndef COMMAND_TOKEN_HPP
#define COMMAND_TOKEN_HPP

#include <string>
#include <vector>
using namespace std;


//Representa los tipos de tokens
enum class TokenType {Word,Parameter,Equal,QuotedValue,EndOfLine,Invalid};


//Tipo de token y el texto que representa
struct Token {TokenType type; string text;};

struct TokenizeResult //Resultados de la tokenizacion
{vector<Token> tokens; vector<string> errors;};

//Clase que tokeniza la entrada...Creo
class CommandToken {
public: TokenizeResult tokenize(const std::string& inputText) const; 

private:
    bool isSeparator(char character) const; //define variable de separadores
}; 
#endif