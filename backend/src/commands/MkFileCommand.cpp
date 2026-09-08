#include "commands/MkFileCommand.hpp"

#include <algorithm>
using namespace std;

namespace{
bool validInt(const string& text, int& number){
    try{
        size_t usedChars = 0;
        number = stoi(text, &usedChars);
        return usedChars == text.size();
    }catch (...){
        return false;
    }
}

string createNumberContent(int fileSize){
    string content;
    for (int pos = 0; pos < fileSize; pos++){
        content += static_cast<char>('0' + (pos % 10));
    }
    return content;
}
}

ValidationResult MkFileCommand::execute(
    const ParsedCommand& command,
    SimulState& state
) const{

    //parametros permitidos
    const std::vector<std::string> allowed = {"path", "r", "size", "cont"};

    for (const ParsedParam& param : command.params){

        //permitido?
        if (find(allowed.begin(), allowed.end(), param.name) == allowed.end()){
            return {false, "MKFILE: parametro no permitido -" + param.name + "."};
        }

        //repetido?
        if (command.countParam(param.name) > 1){
            return {false, "MKFILE: el parametro -" + param.name + " esta repetido."};
        }

        //valido?
        if (param.name == "r"){
            if (param.hasValue){
                return {false, "MKFILE: -r es una bandera y no lleva valor."};
            }
        } else if (!param.hasValue){
            return {false, "MKFILE: el parametro -" + param.name + " necesita un valor."};
        }
    }

    //param obligatorio
    if (!command.hasParam("path")){
        return {false, "MKFILE: -path es obligatorio."};
    }

    //vacio?
    string filePath = command.getParam("path");
    if (filePath.empty()){
        return {false, "MKFILE: -path no puede estar vacio."};
    }

    //valor valido?
    int fileSize = 0;
    if (command.hasParam("size")){
        if (!validInt(command.getParam("size"), fileSize) || fileSize < 0){
            return {false, "MKFILE: -size debe ser cero o un numero positivo."};
        }
    }

    //existe?
    if (state.fileExists(filePath)){
        return {false, "MKFILE: el archivo simulado ya existe; no se sobreescribio."};
    }

    bool recursive = command.hasParam("r");
    string fileContent;

    //contenido
    if (command.hasParam("cont")){
        fileContent = "Contenido simulado desde: " + command.getParam("cont");
    } else{
        fileContent = createNumberContent(fileSize);
    }

    state.files.push_back({filePath, fileSize, recursive, fileContent});

    return {true, "MKFILE: archivo simulado creado: " + filePath + "."};
}
