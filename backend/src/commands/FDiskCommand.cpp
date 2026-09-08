#include "commands/FDiskCommand.hpp"

#include <algorithm>
#include <cctype>
using namespace std;


namespace{

string upperText(string text){
    for (char& character : text){
        character = static_cast<char>(toupper(static_cast<unsigned char>(character)));
    }
    return text;
}

bool validInt(const string& text, int& number){
    try{
        size_t usedChar = 0;
        number = stoi(text, &usedChar);
        return usedChar == text.size();
    }
    catch (...){
        return false;
    }
}
}


ValidationResult FDiskCommand::execute(
    const ParsedCommand& command,
    SimulState& state
) const{
    //parametros permitidos
    const vector<string> allowed = {
        "size", "unit", "path", "type", "fit", "name"
    };

    //validacion de params
    for (const ParsedParam& param : command.params){
        //permitido?
        if (find(allowed.begin(), allowed.end(), param.name) == allowed.end()){
            return {false, "FDISK: parametro no permitido -" + param.name + "."};
        }

        //necesita valor?
        if (!param.hasValue){
            return {false, "FDISK: el parametro -" + param.name + " necesita un valor."};
        }

        //repetido?
        if (command.countParam(param.name) > 1){
            return {false, "FDISK: el parametro -" + param.name + " esta repetido."};
        }
    }

    //param obligatorio
    if (!command.hasParam("size") ||!command.hasParam("path") ||!command.hasParam("name")){
        return {false, "FDISK: -size, -path y -name son obligatorios."};
    }

    //valor valido?
    int partitionSize = 0;
    if (!validInt(command.getParam("size"), partitionSize) || partitionSize <= 0)
    {
        return {false, "FDISK: -size debe ser un numero mayor que cero."};
    }

    //unidad valida?
    string partitionUnit = command.hasParam("unit")? upperText(command.getParam("unit")): "K";

    if (partitionUnit != "B" && partitionUnit != "K" && partitionUnit != "M"){
        return {false, "FDISK: -unit solo acepta B, K o M."};
    }

    //tipo valido?
    string partitionType = command.hasParam("type")? upperText(command.getParam("type")): "P";

    if (partitionType != "P" && partitionType != "E" && partitionType != "L")
    {
        return {false, "FDISK: -type solo acepta P, E o L."};
    }

    //fit valido?
    string partitionFit = "";
    if (command.hasParam("fit")){
        partitionFit = upperText(command.getParam("fit"));
        if (partitionFit != "BF" && partitionFit != "FF" && partitionFit != "WF"){
            return {false, "FDISK: -fit solo acepta BF, FF o WF."};
        }
    }

    //simula crear particion
    string diskPath = command.getParam("path");
    string partitionName = command.getParam("name");

    //existe?
    if (!state.diskExists(diskPath)){
        return {false, "FDISK: el disco simulado indicado en -path no existe."};
    }

    //nombre vacio?
    if (partitionName.empty()){
        return {false, "FDISK: -name no puede estar vacio."};
    }

    //existe el nombre?
    if (state.partitionExists(diskPath, partitionName)){
        return {false, "FDISK: ya existe una particion con ese nombre en el disco."};
    }

    //extendida ya existe?
    if (partitionType == "E" && state.extendedPartitionExists(diskPath)){
        return {false, "FDISK: el disco ya tiene una particion extendida."};
    }

    state.partitions.push_back({
        diskPath,
        partitionName,
        partitionSize,
        partitionUnit,
        partitionType,
        partitionFit
    });

    return {true, "FDISK: particion simulada creada: " + partitionName + "."};
}
