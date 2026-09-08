#include "commands/RmUsrCommand.hpp"

ValidationResult RmUsrCommand::execute(
    const ParsedCommand& command,
    SimulState& state
) const{

    //parametros permitidos
    if (command.params.size() != 1 || !command.hasParam("user")){
        return {false, "RMUSR: solo se permite el parametro obligatorio -user."};
    }

    //necesita valor?
    if (!command.paramHasValue("user")){
        return {false, "RMUSR: -user necesita un valor."};
    }

    std::string username = command.getParam("user");

    //existe usuario?
    if (!state.userExists(username)){
        return {false, "RMUSR: el usuario no existe."};
    }

    state.removeUser(username);
    return {true, "RMUSR: usuario simulado eliminado: " + username + "."};
}
