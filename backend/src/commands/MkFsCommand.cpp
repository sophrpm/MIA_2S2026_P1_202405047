#include "commands/MkFsCommand.hpp"

#include <cctype>
using namespace std;

namespace{
string lowerText(string text){
    for (char& character : text){
        character = static_cast<char>(std::tolower(static_cast<unsigned char>(character)));
    }
    return text;
}
}


ValidationResult MkFsCommand::execute(
    const ParsedCommand& command,
    SimulState& state
) const{
    for (const ParsedParam& param : command.params){

        //permitido?
        if (param.name != "id" && param.name != "type"){
            return {false, "MKFS: parametro no permitido -" + param.name + "."};
        }

        //necesita valor?
        if (!param.hasValue){
            return {false, "MKFS: el parametro -" + param.name + " necesita un valor."};
        }

        //repetido?
        if (command.countParam(param.name) > 1){
            return {false, "MKFS: el parametro -" + param.name + " esta repetido."};
        }
    }

    //param obligatorio
    if (!command.hasParam("id")){
        return {false, "MKFS: -id es obligatorio."};
    }

    //valor valido?
    string formatType = command.hasParam("type")? lowerText(command.getParam("type")): "full";

    if (formatType != "full"){
        return {false, "MKFS: -type solo acepta full."};
    }

    //existe?
    SimulMount* mountedPartition = state.findMount(command.getParam("id"));
    if (mountedPartition == nullptr){
        return {false, "MKFS: no existe una particion montada con ese id."};
    }
    //formatear
    mountedPartition->formatted = true;
    return {true, "MKFS: formato EXT2 simulado aplicado al id " + mountedPartition->id + "."};
}
