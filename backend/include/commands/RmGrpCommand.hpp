#ifndef RMGRP_COMMAND_HPP
#define RMGRP_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "state/AppState.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Maneja el comando rmgrp
class RmGrpCommand {
public:

    //Ejecuta rmgrp
    ValidationResult execute(const ParsedCommand& command, AppState& appState) const;
};


#endif