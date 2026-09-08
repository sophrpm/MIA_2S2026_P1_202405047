#include "commands/MountCommand.hpp"

ValidationResult MountCommand::execute(
    const ParsedCommand& command,
    SimulState& state
) const{

    //parametros permitidos
    for (const ParsedParam& param : command.params){
        if (param.name != "path" && param.name != "name"){
            return {false, "MOUNT: parametro no permitido -" + param.name + "."};
        }

        //necesita valor?
        if (!param.hasValue){
            return {false, "MOUNT: el parametro -" + param.name + " necesita un valor."};
        }

        //repetido?
        if (command.countParam(param.name) > 1){
            return {false, "MOUNT: el parametro -" + param.name + " esta repetido."};
        }
    }

    //param obligatorio
    if (!command.hasParam("path") || !command.hasParam("name")){
        return {false, "MOUNT: -path y -name son obligatorios."};
    }

    std::string diskPath = command.getParam("path");
    std::string partitionName = command.getParam("name");

    //existe disco?
    if (!state.diskExists(diskPath)){
        return {false, "MOUNT: el disco simulado no existe."};
    }

    //existe particion?
    if (!state.partitionExists(diskPath, partitionName)){
        return {false, "MOUNT: la particion simulada no existe."};
    }
    
    //ya esta montada?
    if (state.mountExists(diskPath, partitionName)){
        return {false, "MOUNT: la particion ya esta montada."};
    }

    std::string mountId = state.createMountId();
    state.mounts.push_back({mountId, diskPath, partitionName, false});

    return {true, "MOUNT: particion montada con id " + mountId + "."};
}
