#ifndef MOUNT_COMMAND_HPP
#define MOUNT_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

class MountCommand{
public: ValidationResult execute(const ParsedCommand& command,SimulState& state) const;
};

#endif
