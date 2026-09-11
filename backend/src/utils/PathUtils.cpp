#include "utils/PathUtils.hpp"

#include <filesystem>

using namespace std;


//Crea las carpetas necesarias para una ruta
bool PathUtils::createDirectories(const string& path){
    string parentPath = getParentPath(path);

    if (parentPath.empty()){
        return true;
    }

    if (filesystem::exists(parentPath)){
        return true;
    }

    return filesystem::create_directories(parentPath);
}


//Obtiene la carpeta padre de una ruta
string PathUtils::getParentPath(const string& path){
    filesystem::path filePath(path);

    return filePath.parent_path().string();
}


//Obtiene el nombre del archivo
string PathUtils::getFileName(const string& path){
    filesystem::path filePath(path);

    return filePath.filename().string();
}


//Obtiene la extension del archivo
string PathUtils::getExtension(const string& path){
    filesystem::path filePath(path);
    string extension = filePath.extension().string();

    //quita el punto de la extension
    if (!extension.empty() && extension[0] == '.'){
        extension.erase(0, 1);
    }

    return extension;
}


//Verifica si una ruta termina en una extension
bool PathUtils::hasExtension(const string& path, const string& extension){
    string pathExtension = getExtension(path);

    if (pathExtension.size() != extension.size()){
        return false;
    }

    for (size_t position = 0; position < pathExtension.size(); position++){
        char pathCharacter = pathExtension[position];
        char extensionCharacter = extension[position];

        if (pathCharacter >= 'A' && pathCharacter <= 'Z'){
            pathCharacter = pathCharacter - 'A' + 'a';
        }

        if (extensionCharacter >= 'A' && extensionCharacter <= 'Z'){
            extensionCharacter = extensionCharacter - 'A' + 'a';
        }

        if (pathCharacter != extensionCharacter){
            return false;
        }
    }

    return true;
}


//Verifica si la ruta es absoluta
bool PathUtils::isAbsolute(const string& path){
    filesystem::path filePath(path);

    return filePath.is_absolute();
}