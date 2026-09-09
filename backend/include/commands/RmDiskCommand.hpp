#ifndef RMDISK_COMMAND_HPP
#define RMDISK_COMMAND_HPP

#include "analysis/ParsedCommand.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Maneja el comando rmdisk
class RmDiskCommand {
public:

    //Ejecuta rmdisk
    ValidationResult execute(const ParsedCommand& command) const;
};


#endif