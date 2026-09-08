#ifndef MKFILE_COMMAND_HPP
#define MKFILE_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

class MkFileCommand{
public: ValidationResult execute(const ParsedCommand& command, SimulState& state) const;
};

#endif
