#ifndef FDISK_COMMAND_HPP
#define FDISK_COMMAND_HPP

#include <string>

#include "analysis/ParsedCommand.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Maneja el comando fdisk
class FDiskCommand {
public:

    //Ejecuta fdisk
    ValidationResult execute(const ParsedCommand& command) const;


private:

    //Convierte tamaño y unidad a bytes
    long long getSizeInBytes(int size, const string& unit) const;

    //Obtiene tipo de particion
    char getType(const string& type) const;

    //Obtiene fit de particion
    char getFit(const string& fit) const;

    //Verifica si se quiere eliminar
    bool isDeleteOperation(const ParsedCommand& command) const;

    //Verifica si se quiere modificar tamaño
    bool isAddOperation(const ParsedCommand& command) const;
};


#endif