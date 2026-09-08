#include "analysis/CommandParser.hpp"

#include <cctype>
using namespace std;

string CommandParser::toLower(const string& text) const{
    string lowerText = text;
    for (char& character : lowerText){
        character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
    }
    return lowerText;
}

ParseResult CommandParser::parse(const vector<Token>& tokens) const{
    ParseResult result;
    size_t tokenPos = 0;
    //recorre tokens y parsea
    while (tokenPos < tokens.size()){
        //Ignora fin de line
        while (tokenPos < tokens.size() && tokens[tokenPos].type == TokenType::EndOfLine){
            tokenPos++;
        }

        //Si se acaban los tokens muere
        if (tokenPos >= tokens.size()){
            break;
        }

        //Si es invalid muere
        if (tokens[tokenPos].type == TokenType::Invalid){
            result.errors.push_back("Error sintactico: hay un token invalido en el comando.");
            while (tokenPos < tokens.size() &&tokens[tokenPos].type != TokenType::EndOfLine){
                tokenPos++;
            }
            continue;
        }

        //si no es word muere
        if (tokens[tokenPos].type != TokenType::Word){
            result.errors.push_back("Error sintactico: se esperaba el nombre de un comando.");
            while (tokenPos < tokens.size() && tokens[tokenPos].type != TokenType::EndOfLine){
                tokenPos++;
            }
            continue;
        }

        //Comando parseado
        ParsedCommand parsedCommand;
        parsedCommand.name = toLower(tokens[tokenPos].text);
        tokenPos++;

        bool commandHasError = false;

        //recorre y parsea param
        while (tokenPos < tokens.size() &&tokens[tokenPos].type != TokenType::EndOfLine)
        {
            if (tokens[tokenPos].type != TokenType::Parameter){
                result.errors.push_back("Error sintactico en " + parsedCommand.name +": se esperaba un parametro.");
                commandHasError = true;
                break;
            }

            ParsedParam parsedParam;
            std::string completeParam = tokens[tokenPos].text;
            parsedParam.name = toLower(completeParam.substr(1));
            parsedParam.value = "";
            parsedParam.hasValue = false;
            tokenPos++;

            //si =busca valor
            if (tokenPos < tokens.size() &&tokens[tokenPos].type == TokenType::Equal){
                tokenPos++;

                //si eciste valor o error
                if (tokenPos >= tokens.size() ||tokens[tokenPos].type == TokenType::EndOfLine || (tokens[tokenPos].type != TokenType::Word && tokens[tokenPos].type != TokenType::QuotedValue)){
                    result.errors.push_back("Error sintactico en " + parsedCommand.name +": falta el valor de -" + parsedParam.name + ".");
                    commandHasError = true;
                    break;
                }

                //si valid lo guaeda
                parsedParam.value = tokens[tokenPos].text;
                parsedParam.hasValue = true;
                tokenPos++;
            }

            parsedCommand.params.push_back(parsedParam);
        }

        //si error ignora hasta finln
        if (commandHasError){
            while (tokenPos < tokens.size() && tokens[tokenPos].type != TokenType::EndOfLine){
                tokenPos++;
            }
        }else{ result.commands.push_back(parsedCommand);}

        //si finln ignora
        if (tokenPos < tokens.size() &&tokens[tokenPos].type == TokenType::EndOfLine) {
            tokenPos++;
        }
    }

    return result;
}