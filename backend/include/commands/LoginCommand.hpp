#ifndef LOGIN_COMMAND_HPP
#define LOGIN_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "state/AppState.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Maneja el comando login
class LoginCommand {
public:

    //Ejecuta login
    ValidationResult execute(const ParsedCommand& command, AppState& appState) const;
};


#endif