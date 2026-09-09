#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>

#include "structures/Ext2Structures.hpp"

using namespace std;

struct AppState;


//Maneja archivos, carpetas y rutas dentro de EXT2
class FileManager {
public:

    //Crea una carpeta dentro del sistema
    bool createDirectory(const string& path, bool recursive, AppState& appState, string& message) const;

    //Crea un archivo dentro del sistema
    bool createFile(const string& path, const string& content, bool recursive, bool overwrite, AppState& appState, string& message) const;

    //Lee el contenido de un archivo
    bool readFile(const string& path, const AppState& appState, string& content, string& message) const;

    //Reemplaza el contenido de un archivo
    bool writeFile(const string& path, const string& content, AppState& appState, string& message) const;

    //Busca el inodo que corresponde a una ruta
    bool findInodeByPath(const string& path, const AppState& appState, int& inodeIndex, Inode& inode, string& message) const;

    //Obtiene las entradas de una carpeta
    bool getDirectoryContent(const string& path, const AppState& appState, vector<Content>& entries, string& message) const;

    //Verifica si una ruta ya existe
    bool pathExists(const string& path, const AppState& appState) const;

private:

    //Divide una ruta en sus partes
    vector<string> splitPath(const string& path) const;

    //Busca una entrada dentro de una carpeta
    int findEntry(const string& diskPath, const SuperBlock& superBlock, const Inode& directoryInode, const string& name) const;

    //Busca espacio libre dentro de una carpeta
    bool findFreeDirectoryEntry(const string& diskPath, int partitionStart, SuperBlock& superBlock, int directoryInodeIndex, Inode& directoryInode, int& blockIndex, int& entryIndex) const;

    //Agrega una entrada dentro de una carpeta
    bool addDirectoryEntry(const string& diskPath, int partitionStart, SuperBlock& superBlock, int directoryInodeIndex, Inode& directoryInode, const string& name, int newInodeIndex) const;

    //Crea una carpeta individual
    bool createSingleDirectory(const string& diskPath, int partitionStart, SuperBlock& superBlock, int parentInodeIndex, const string& name, int uid, int gid, int& newInodeIndex) const;

    //Crea el inodo de un archivo
    bool createFileInode(const string& diskPath, int partitionStart, SuperBlock& superBlock, int uid, int gid, const string& content, int& inodeIndex) const;

    //Escribe contenido dentro de los bloques de un archivo
    bool writeFileContent(const string& diskPath, int partitionStart, SuperBlock& superBlock, int inodeIndex, Inode& inode, const string& content) const;

    //Lee todos los bloques de un archivo
    bool readFileContent(const string& diskPath, const SuperBlock& superBlock, const Inode& inode, string& content) const;

    //Obtiene un bloque usando los apuntadores del inodo
    int getDataBlock(const string& diskPath, const SuperBlock& superBlock, const Inode& inode, int logicalBlock) const;

    //Asigna un bloque al inodo
    bool setDataBlock(const string& diskPath, int partitionStart, SuperBlock& superBlock, Inode& inode, int logicalBlock, int blockIndex) const;

    //Maneja apuntador indirecto simple
    int getSimpleIndirectBlock(const string& diskPath, const SuperBlock& superBlock, int pointerBlockIndex, int position) const;

    //Maneja apuntador indirecto doble
    int getDoubleIndirectBlock(const string& diskPath, const SuperBlock& superBlock, int pointerBlockIndex, int position) const;

    //Maneja apuntador indirecto triple
    int getTripleIndirectBlock(const string& diskPath, const SuperBlock& superBlock, int pointerBlockIndex, int position) const;

    //Asigna usando apuntador indirecto simple
    bool setSimpleIndirectBlock(const string& diskPath, int partitionStart, SuperBlock& superBlock, Inode& inode, int logicalBlock, int blockIndex) const;

    //Asigna usando apuntador indirecto doble
    bool setDoubleIndirectBlock(const string& diskPath, int partitionStart, SuperBlock& superBlock, Inode& inode, int logicalBlock, int blockIndex) const;

    //Asigna usando apuntador indirecto triple
    bool setTripleIndirectBlock(const string& diskPath, int partitionStart, SuperBlock& superBlock, Inode& inode, int logicalBlock, int blockIndex) const;

    //Libera los bloques usados por un archivo
    bool freeFileBlocks(const string& diskPath, int partitionStart, SuperBlock& superBlock, Inode& inode) const;

    //Verifica permiso de lectura
    bool canRead(const Inode& inode, int uid, int gid) const;

    //Verifica permiso de escritura
    bool canWrite(const Inode& inode, int uid, int gid) const;

    //Obtiene el permiso que corresponde al usuario
    int getPermission(const Inode& inode, int uid, int gid) const;
};


#endif