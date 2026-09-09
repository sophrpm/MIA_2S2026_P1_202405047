#ifndef PATH_UTILS_HPP
#define PATH_UTILS_HPP

#include <string>

using namespace std;


//Utilidades para trabajar con rutas
class PathUtils {
public:

    //Crea las carpetas necesarias para una ruta
    static bool createDirectories(const string& path);

    //Obtiene la carpeta padre de una ruta
    static string getParentPath(const string& path);

    //Obtiene el nombre del archivo
    static string getFileName(const string& path);

    //Obtiene la extension del archivo
    static string getExtension(const string& path);

    //Verifica si una ruta termina en una extension
    static bool hasExtension(const string& path, const string& extension);

    //Verifica si la ruta es absoluta
    static bool isAbsolute(const string& path);
};


#endif