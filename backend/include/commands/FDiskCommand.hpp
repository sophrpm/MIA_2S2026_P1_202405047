#ifndef FDISK_COMMAND_HPP
#define FDISK_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

class FDiskCommand{
public: ValidationResult execute(const ParsedCommand& command, SimulState& state) const;
};

#endif
