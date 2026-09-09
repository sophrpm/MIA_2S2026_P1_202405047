#ifndef LOGOUT_COMMAND_HPP
#define LOGOUT_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "state/AppState.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Maneja el comando logout
class LogoutCommand {
public:

    //Ejecuta logout
    ValidationResult execute(const ParsedCommand& command, AppState& appState) const;
};


#endif