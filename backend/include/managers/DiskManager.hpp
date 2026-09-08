#ifndef DISK_MANAGER_HPP
#define DISK_MANAGER_HPP

#include <string>
#include <vector>

#include "structures/DiskStructures.hpp"

using namespace std;


//Maneja los discos .mia y sus particiones
class DiskManager {
public:

    //Crea disco y escribe el MBR
    bool createDisk(const string& path, int sizeBytes, char fit, string& message) const;

    //Elimina un disco existente
    bool removeDisk(const string& path, string& message) const;

    //Crea particion primaria, extendida o logica
    bool createPartition(const string& path, int sizeBytes, char type, char fit, const string& name, string& message) const;

    //Elimina una particion del disco
    bool deletePartition(const string& path, const string& name, string& message) const;

    //Lee el MBR de un disco
    bool readMBR(const string& path, MBR& mbr) const;

    //Escribe cambios en el MBR
    bool writeMBR(const string& path, const MBR& mbr) const;

    //Busca una particion primaria o extendida por nombre
    int findPartition(const MBR& mbr, const string& name) const;

    //Busca una particion logica por nombre
    bool findLogicalPartition(const string& path, const string& name, EBR& ebr, int& ebrPosition) const;

private:

    //Representa un espacio libre encontrado
    struct FreeSpace {
        int start;
        int size;
    };

    //Verifica si el archivo existe
    bool diskExists(const string& path) const;

    //Verifica extension .mia
    bool validExtension(const string& path) const;

    //Verifica si el nombre ya existe
    bool partitionNameExists(const string& path, const MBR& mbr, const string& name) const;

    //Busca la particion extendida
    int findExtendedPartition(const MBR& mbr) const;

    //Busca posicion libre dentro del MBR
    int findFreePartitionSlot(const MBR& mbr) const;

    //Obtiene espacios libres del disco
    vector<FreeSpace> getDiskFreeSpaces(const MBR& mbr) const;

    //Escoge espacio segun FF, BF o WF
    int chooseSpace(const vector<FreeSpace>& freeSpaces, int requiredSize, char fit) const;

    //Crea primaria o extendida
    bool createPrimaryOrExtended(const string& path, MBR& mbr, int sizeBytes, char type, char fit, const string& name, string& message) const;

    //Crea una particion logica
    bool createLogical(const string& path, MBR& mbr, int sizeBytes, char fit, const string& name, string& message) const;

    //Escribe el primer EBR de una extendida
    bool createFirstEBR(const string& path, const Partition& extendedPartition) const;

    //Elimina primaria o extendida
    bool deletePrimaryOrExtended(const string& path, MBR& mbr, int partitionIndex, string& message) const;

    //Elimina una particion logica
    bool deleteLogical(const string& path, const string& name, string& message) const;

    //Llena una parte del disco con ceros
    bool clearSpace(const string& path, int start, int size) const;
};


#endif