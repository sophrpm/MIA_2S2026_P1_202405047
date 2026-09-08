#include "commands/MkUsrCommand.hpp"


ValidationResult MkUsrCommand::execute(
    const ParsedCommand& command,
    SimulState& state
) const{
    for (const ParsedParam& param : command.params){

        //permitido?
        if (param.name != "user" &&param.name != "pass" && param.name != "grp"){
            return {false, "MKUSR: parametro no permitido -" + param.name + "."};
        }

        //necesita valor?
        if (!param.hasValue){
            return {false, "MKUSR: el parametro -" + param.name + " necesita un valor."};
        }
        //repetido?
        if (command.countParam(param.name) > 1){
            return {false, "MKUSR: el parametro -" + param.name + " esta repetido."};
        }
    }

    //param obligatorio
    if (!command.hasParam("user") || !command.hasParam("pass") || !command.hasParam("grp")){
        return {false, "MKUSR: -user, -pass y -grp son obligatorios."};
    }

    string username = command.getParam("user");
    string password = command.getParam("pass");
    string group = command.getParam("grp");

    //vacio?
    if (username.empty() || password.empty() || group.empty()){
        return {false, "MKUSR: los valores no pueden estar vacios."};
    }

    //demasiado largo?
    if (username.size() > 10 || password.size() > 10 || group.size() > 10){
        return {false, "MKUSR: user, pass y grp deben tener maximo 10 caracteres."};
    }

    //existe?
    if (state.userExists(username)){
        return {false, "MKUSR: el usuario ya existe."};
    }

    state.users.push_back({username, password, group, true});
    return {true, "MKUSR: usuario simulado creado: " + username + "."};
}
