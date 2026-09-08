#ifndef RMUSR_COMMAND_HPP
#define RMUSR_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

class RmUsrCommand{
public: ValidationResult execute(const ParsedCommand& command,SimulState& state) const;
};

#endif
