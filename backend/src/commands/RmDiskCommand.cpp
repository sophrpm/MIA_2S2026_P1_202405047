#include "commands/RmDiskCommand.hpp"

ValidationResult RmDiskCommand::execute(
    const ParsedCommand& command,
    SimulState& state
) const{
    //parametros permitidos
    if (command.params.size() != 1 || !command.hasParam("path")){
        return {false, "RMDISK: solo se permite el parametro obligatorio -path."};
    }

    //necesita valor?
    if (!command.paramHasValue("path")){
        return {false, "RMDISK: -path necesita un valor."};
    }

    std::string diskPath = command.getParam("path");

    //existe disco?
    if (!state.diskExists(diskPath)){
        return {false, "RMDISK: el disco simulado no existe."};
    }

    state.removeDisk(diskPath);
    return {true, "RMDISK: disco simulado eliminado: " + diskPath + "."};
}
