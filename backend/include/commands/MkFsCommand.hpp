#ifndef MKFS_COMMAND_HPP
#define MKFS_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

class MkFsCommand{
public: ValidationResult execute(const ParsedCommand& command,SimulState& state) const;
};

#endif
