#ifndef BINARY_UTILS_HPP
#define BINARY_UTILS_HPP

#include <fstream>
#include <string>

using namespace std;


//Utilidades para leer y escribir archivos binarios
class BinaryUtils {
public:

    //Lee una estructura desde una posicion del archivo
    template <typename T>
    static bool readStruct(const string& path, int position, T& data){
        fstream file(path, ios::in | ios::binary);

        if (!file.is_open()){
            return false;
        }

        file.seekg(position, ios::beg);

        if (!file.good()){
            file.close();
            return false;
        }

        file.read(reinterpret_cast<char*>(&data), sizeof(T));

        bool readOk = file.good();
        file.close();

        return readOk;
    }

    //Escribe una estructura en una posicion del archivo
    template <typename T>
    static bool writeStruct(const string& path, int position, const T& data){
        fstream file(path, ios::in | ios::out | ios::binary);

        if (!file.is_open()){
            return false;
        }

        file.seekp(position, ios::beg);

        if (!file.good()){
            file.close();
            return false;
        }

        file.write(reinterpret_cast<const char*>(&data), sizeof(T));

        bool writeOk = file.good();
        file.close();

        return writeOk;
    }

    //Llena un espacio del archivo con ceros
    static bool clearSpace(const string& path, int start, int size);

    //Verifica si existe un archivo
    static bool fileExists(const string& path);

    //Obtiene el tamaño de un archivo
    static long long getFileSize(const string& path);

    //Copia texto a un arreglo char fijo
    static void copyToFixedChar(char* destination, int size, const string& text);

    //Convierte arreglo char fijo a string
    static string fixedCharToString(const char* text, int size);
};


#endif