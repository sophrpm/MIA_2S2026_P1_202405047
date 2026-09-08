#include "commands/MkDiskCommand.hpp"

#include <algorithm>
#include <cctype>
using namespace std;

namespace{

string upperText(string text){
    for (char& character : text){
        character = static_cast<char>(std::toupper(static_cast<unsigned char>(character)));
    }
    return text;
}

bool validInt(const std::string& text, int& number){
    try{
        size_t usedChars = 0;
        number = stoi(text, &usedChars);
        return usedChars == text.size();
    }
    catch (...){
        return false;
    }
}
}

ValidationResult MkDiskCommand::execute(
    const ParsedCommand& command,
    SimulState& state
) const{

    //parametros permitidos
    const vector<string> allowed = {"size", "fit", "unit", "path"};

    //validacion de params
    for (const ParsedParam& param : command.params){
        //permitido?
        if (find(allowed.begin(), allowed.end(), param.name) == allowed.end()){
            return {false, "MKDISK: parametro no permitido -" + param.name + "."};
        }

        //necesita valor?
        if (!param.hasValue){
            return {false, "MKDISK: el parametro -" + param.name + " necesita un valor."};
        }

        //repetido?
        if (command.countParam(param.name) > 1){
            return {false, "MKDISK: el parametro -" + param.name + " esta repetido."};
        }
    }

    //param obligatorio
    if (!command.hasParam("size") || !command.hasParam("path")){
        return {false, "MKDISK: -size y -path son obligatorios."};
    }

    //valor valido?
    int diskSize = 0;
    if (!validInt(command.getParam("size"), diskSize) || diskSize <= 0){
        return {false, "MKDISK: -size debe ser un numero mayor que cero."};
    }

    //unidad valida?
    string diskUnit = command.hasParam("unit")? upperText(command.getParam("unit")): "M";

    if (diskUnit != "K" && diskUnit != "M"){
        return {false, "MKDISK: -unit solo acepta K o M."};
    }

    //fit valido?
    string diskFit = command.hasParam("fit")? upperText(command.getParam("fit")): "FF";

    if (diskFit != "BF" && diskFit != "FF" && diskFit != "WF"){
        return {false, "MKDISK: -fit solo acepta BF, FF o WF."};
    }

    //path valido?
    string diskPath = command.getParam("path");
    if (diskPath.empty()){
        return {false, "MKDISK: -path no puede estar vacio."};
    }

    if (state.diskExists(diskPath)){
        return {false, "MKDISK: ya existe un disco simulado con esa ruta."};
    }

    state.disks.push_back({diskPath, diskSize, diskUnit, diskFit});

    return {
        true,
        "MKDISK: disco simulado creado en " + diskPath +" con tamano " + std::to_string(diskSize) + " " + diskUnit + "."
    };
}
