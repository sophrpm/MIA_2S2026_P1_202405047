#ifndef MKDISK_COMMAND_HPP
#define MKDISK_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

class MkDiskCommand{
public: ValidationResult execute( const ParsedCommand& command, SimulState& state) const;
};

#endif
