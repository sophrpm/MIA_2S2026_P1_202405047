#ifndef PARSED_COMMAND_HPP
#define PARSED_COMMAND_HPP

#include <string>
#include <vector>
using namespace std;


struct ParsedParam{string name; string value;bool hasValue;};

struct ParsedCommand{ string name; vector<ParsedParam> params;

    bool hasParam(const string& parameterName) const{
        //verifica que exista parametro .-.-.
        for (const ParsedParam& param : params){
            if (param.name == parameterName) {
                return true;
            }
        }
        return false;
    }

    // Obtiene el value sino vacio
    std::string getParam(const std::string& parameterName) const {
        for (const ParsedParam& param : params){
            if (param.name == parameterName){
                return param.value;
            }
        }
        return "";
    }

    bool paramHasValue(const string& parameterName) const{
        for (const ParsedParam& param : params){
            if (param.name == parameterName){
                return param.hasValue;
            }
        }
        return false;
    }

    int countParam(const string& parameterName) const{
        int amount = 0;
        for (const ParsedParam& param : params ){
            if (param.name == parameterName){
                amount++;
            }
        }
        return amount;
    }
};

#endif