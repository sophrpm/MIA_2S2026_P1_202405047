#ifndef PARSED_COMMAND_HPP
#define PARSED_COMMAND_HPP

#include <string>
#include <vector>

using namespace std;

//Representa un parametro encontrado dentro de un comando
struct ParsedParam {
    string name;
    string value;
    bool hasValue;
};

//Representa un comando que ya fue procesado por el parser
struct ParsedCommand {
    string name;
    vector<ParsedParam> params;

    //Se utiliza cuando la linea corresponde a un comentario
    bool isComment = false;
    string commentText = "";

    //Verifica si el comando contiene un parametro
    bool hasParam(const string& parameterName) const {
        for (const ParsedParam& param : params) {
            if (param.name == parameterName) {
                return true;
            }
        }

        return false;
    }

    //Devuelve el valor de un parametro
    string getParam(const string& parameterName) const {
        for (const ParsedParam& param : params) {
            if (param.name == parameterName) {
                return param.value;
            }
        }

        return "";
    }

    //Indica si un parametro fue escrito con un valor
    bool paramHasValue(const string& parameterName) const {
        for (const ParsedParam& param : params) {
            if (param.name == parameterName) {
                return param.hasValue;
            }
        }

        return false;
    }

    //Cuenta cuantas veces aparece un parametro
    int countParam(const string& parameterName) const {
        int amount = 0;

        for (const ParsedParam& param : params) {
            if (param.name == parameterName) {
                amount++;
            }
        }

        return amount;
    }

    //Facilita la validacion de parametros repetidos
    bool hasRepeatedParam(const string& parameterName) const {
        return countParam(parameterName) > 1;
    }
};

#endif