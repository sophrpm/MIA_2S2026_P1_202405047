#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <string>
#include <vector>

#include "analysis/CommandToken.hpp"
#include "analysis/ParsedCommand.hpp"
using namespace std;

//Res del parseo
struct ParseResult{
    vector<ParsedCommand> commands;
    vector<std::string> errors;
};

//Clase que parsea da res
class CommandParser{
public: ParseResult parse(const vector<Token>& tokens) const;

private:string toLower(const string& text) const;
};

#endif