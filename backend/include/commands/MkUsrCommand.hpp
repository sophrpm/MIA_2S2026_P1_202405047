#ifndef MKUSR_COMMAND_HPP
#define MKUSR_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "state/AppState.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Maneja el comando mkusr
class MkUsrCommand {
public:

    //Ejecuta mkusr
    ValidationResult execute(const ParsedCommand& command, AppState& appState) const;
};


#endif