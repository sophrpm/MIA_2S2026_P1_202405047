#ifndef MKUSR_COMMAND_HPP
#define MKUSR_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

class MkUsrCommand{
public: ValidationResult execute(const ParsedCommand& command,SimulState& state) const;
};

#endif
