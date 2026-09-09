#ifndef MKDISK_COMMAND_HPP
#define MKDISK_COMMAND_HPP

#include <string>

#include "analysis/ParsedCommand.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Maneja el comando mkdisk
class MkDiskCommand {
public:

    //Ejecuta mkdisk
    ValidationResult execute(const ParsedCommand& command) const;

private:

    //Convierte tamaño y unidad a bytes
    long long getSizeInBytes(int size, const string& unit) const;

    //Convierte fit al valor que usa el disco
    char getFit(const string& fit) const;
};


#endif