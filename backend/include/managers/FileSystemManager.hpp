#ifndef FILE_SYSTEM_MANAGER_HPP
#define FILE_SYSTEM_MANAGER_HPP

#include <string>

#include "structures/Ext2Structures.hpp"

using namespace std;


//Maneja la estructura principal de EXT2
class FileSystemManager {
public:

    //Formatea una particion como EXT2
    bool formatExt2(const string& path, int partitionStart, int partitionSize, string& message) const;

    //Lee el superbloque de una particion
    bool readSuperBlock(const string& path, int partitionStart, SuperBlock& superBlock) const;

    //Escribe cambios del superbloque
    bool writeSuperBlock(const string& path, int partitionStart, const SuperBlock& superBlock) const;

    //Lee un inodo por su posicion
    bool readInode(const string& path, const SuperBlock& superBlock, int inodeIndex, Inode& inode) const;

    //Escribe un inodo por su posicion
    bool writeInode(const string& path, const SuperBlock& superBlock, int inodeIndex, const Inode& inode) const;

    //Lee un bloque carpeta
    bool readFolderBlock(const string& path, const SuperBlock& superBlock, int blockIndex, FolderBlock& folderBlock) const;

    //Escribe un bloque carpeta
    bool writeFolderBlock(const string& path, const SuperBlock& superBlock, int blockIndex, const FolderBlock& folderBlock) const;

    //Lee un bloque archivo
    bool readFileBlock(const string& path, const SuperBlock& superBlock, int blockIndex, FileBlock& fileBlock) const;

    //Escribe un bloque archivo
    bool writeFileBlock(const string& path, const SuperBlock& superBlock, int blockIndex, const FileBlock& fileBlock) const;

    //Lee un bloque de apuntadores
    bool readPointerBlock(const string& path, const SuperBlock& superBlock, int blockIndex, PointerBlock& pointerBlock) const;

    //Escribe un bloque de apuntadores
    bool writePointerBlock(const string& path, const SuperBlock& superBlock, int blockIndex, const PointerBlock& pointerBlock) const;

    //Busca un inodo libre en bitmap
    int findFreeInode(const string& path, const SuperBlock& superBlock) const;

    //Busca un bloque libre en bitmap
    int findFreeBlock(const string& path, const SuperBlock& superBlock) const;

    //Reserva un inodo libre
    int allocateInode(const string& path, int partitionStart, SuperBlock& superBlock) const;

    //Reserva un bloque libre
    int allocateBlock(const string& path, int partitionStart, SuperBlock& superBlock) const;

    //Libera un inodo
    bool freeInode(const string& path, int partitionStart, SuperBlock& superBlock, int inodeIndex) const;

    //Libera un bloque
    bool freeBlock(const string& path, int partitionStart, SuperBlock& superBlock, int blockIndex) const;

    //Lee valor del bitmap de inodos
    bool readInodeBitmap(const string& path, const SuperBlock& superBlock, int inodeIndex, char& value) const;

    //Lee valor del bitmap de bloques
    bool readBlockBitmap(const string& path, const SuperBlock& superBlock, int blockIndex, char& value) const;

private:

    //Calcula cantidad de inodos para EXT2
    int calculateInodes(int partitionSize) const;

    //Inicia el superbloque
    SuperBlock createSuperBlock(int partitionStart, int partitionSize, int inodeCount) const;

    //Limpia la particion antes del formato
    bool clearPartition(const string& path, int partitionStart, int partitionSize) const;

    //Inicia bitmap de inodos
    bool initializeInodeBitmap(const string& path, const SuperBlock& superBlock) const;

    //Inicia bitmap de bloques
    bool initializeBlockBitmap(const string& path, const SuperBlock& superBlock) const;

    //Inicia tabla de inodos
    bool initializeInodes(const string& path, const SuperBlock& superBlock) const;

    //Inicia area de bloques
    bool initializeBlocks(const string& path, const SuperBlock& superBlock) const;

    //Crea raiz y users.txt
    bool createRoot(const string& path, int partitionStart, SuperBlock& superBlock) const;

    //Cambia valor del bitmap de inodos
    bool writeInodeBitmap(const string& path, const SuperBlock& superBlock, int inodeIndex, char value) const;

    //Cambia valor del bitmap de bloques
    bool writeBlockBitmap(const string& path, const SuperBlock& superBlock, int blockIndex, char value) const;

    //Actualiza primer inodo y bloque libre
    void updateFirstFree(const string& path, SuperBlock& superBlock) const;
};


#endif