#ifndef MKFILE_COMMAND_HPP
#define MKFILE_COMMAND_HPP

#include <string>

#include "analysis/ParsedCommand.hpp"
#include "state/AppState.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Maneja el comando mkfile
class MkFileCommand {
public:

    //Ejecuta mkfile
    ValidationResult execute(const ParsedCommand& command, AppState& appState) const;

private:

    //Genera contenido usando 0123456789
    string generateContent(int size) const;

    //Lee contenido desde un archivo del sistema
    bool readExternalFile(const string& path, string& content) const;
};


#endif