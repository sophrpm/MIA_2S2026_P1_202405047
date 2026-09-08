#ifndef RMDISK_COMMAND_HPP
#define RMDISK_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

class RmDiskCommand{
public: ValidationResult execute(const ParsedCommand& command,SimulState& state) const;
};

#endif
