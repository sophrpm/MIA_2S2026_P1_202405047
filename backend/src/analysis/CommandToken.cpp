#include "analysis/CommandToken.hpp"

#include <cctype>
using namespace std;
// Verifica separadores
bool CommandToken::isSeparator(char character) const { return character == ' ' || character == '\t' || character == '\r' || character == '\n' || character == '=' || character == '#';}

//Funcion que tokeniza entrada y devuelve res...
TokenizeResult CommandToken::tokenize(const string& inputText) const {
    TokenizeResult result;
    size_t textPos = 0;

    //bucle que recorre el txt y toknisa
    while (textPos < inputText.size()){
        char currentCharacter = inputText[textPos];

        if (currentCharacter == ' ' || currentCharacter == '\t' || currentCharacter == '\r'){
            textPos++;
            continue;
        }

        //salto de linea:)
        if (currentCharacter == '\n'){
            result.tokens.push_back({TokenType::EndOfLine, "\n"});
            textPos++;
            continue;
        }

        // Ignora linea de comentario:V
        if (currentCharacter == '#'){
            textPos++;
            while (textPos < inputText.size() && inputText[textPos] != '\n')
            {
                textPos++;
            }
            continue;
        }

        //singo igual=
        if (currentCharacter == '='){
            result.tokens.push_back({TokenType::Equal, "="});
            textPos++;
            continue;
        }

        //comilas dobles"value"
        if (currentCharacter == '"'){
            textPos++;
            string quotedText;
            bool closedQuote = false;

            while (textPos < inputText.size()){
                if (inputText[textPos] == '"'){
                    closedQuote = true;
                    textPos++;
                    break;
                }

                if (inputText[textPos] == '\n'){
                    break;
                }

                quotedText += inputText[textPos];
                textPos++;
            }

            if (!closedQuote){
                result.errors.push_back("Error lexico: cadena entre comillas sin cerrar.");
                result.tokens.push_back({TokenType::Invalid, quotedText});
            } else{ result.tokens.push_back({TokenType::QuotedValue, quotedText});
            }
            continue;
        }

        //signo de param-
        if (currentCharacter == '-' && textPos + 1< inputText.size() &&isalpha(static_cast<unsigned char>(inputText[textPos + 1]))){
            string parameterName;
            parameterName += inputText[textPos];
            textPos++;
            //este verifica param bueno
            while (textPos < inputText.size()){
                char parameterCharacter = inputText[textPos ];
                if (!isalnum(static_cast<unsigned char>(parameterCharacter)) && parameterCharacter != '_'){
                    break;
                }

                parameterName += parameterCharacter;
                textPos ++;
            }

            result.tokens.push_back({TokenType::Parameter, parameterName});
            continue;
        }

        string wordText;
        //contiene palabra
        while (textPos < inputText.size() &&!isSeparator(inputText[textPos])){
            if (inputText[textPos] == '"'){
                break;
            }

            wordText += inputText[textPos];
            textPos++;
        }

        if (!wordText.empty()){
            result.tokens.push_back({TokenType::Word, wordText});
            continue;
        }

        //Errres
        result.errors.push_back(
            std::string("Error lexico: simbolo no reconocido '") + currentCharacter + "'.");
        result.tokens.push_back({TokenType::Invalid, std::string(1, currentCharacter)});
        textPos++;
    }

    return result;
}