#include <crow.h>
#include <crow/middlewares/cors.h>

#include <iostream>
#include <string>
#include <vector>

#include "analysis/CommandParser.hpp"
#include "analysis/CommandToken.hpp"
#include "analysis/ParsedCommand.hpp"

#include "commands/CatCommand.hpp"
#include "commands/ChGrpCommand.hpp"
#include "commands/FDiskCommand.hpp"
#include "commands/LoginCommand.hpp"
#include "commands/LogoutCommand.hpp"
#include "commands/MkDirCommand.hpp"
#include "commands/MkDiskCommand.hpp"
#include "commands/MkFileCommand.hpp"
#include "commands/MkFsCommand.hpp"
#include "commands/MkGrpCommand.hpp"
#include "commands/MkUsrCommand.hpp"
#include "commands/MountCommand.hpp"
#include "commands/MountedCommand.hpp"
#include "commands/RepCommand.hpp"
#include "commands/RmDiskCommand.hpp"
#include "commands/RmGrpCommand.hpp"
#include "commands/RmUsrCommand.hpp"

#include "state/AppState.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//Guarda montajes y sesion mientras corre el servidor
AppState appState;


//Ejecuta el comando que corresponde
ValidationResult executeCommand(const ParsedCommand& command){

    if (command.name == "mkdisk"){
        MkDiskCommand mkDiskCommand;
        return mkDiskCommand.execute(command);
    }

    if (command.name == "rmdisk"){
        RmDiskCommand rmDiskCommand;
        return rmDiskCommand.execute(command);
    }

    if (command.name == "fdisk"){
        FDiskCommand fDiskCommand;
        return fDiskCommand.execute(command);
    }

    if (command.name == "mount"){
        MountCommand mountCommand;
        return mountCommand.execute(command, appState);
    }

    if (command.name == "mounted"){
        MountedCommand mountedCommand;
        return mountedCommand.execute(command, appState);
    }

    if (command.name == "mkfs"){
        MkFsCommand mkFsCommand;
        return mkFsCommand.execute(command, appState);
    }

    if (command.name == "login"){
        LoginCommand loginCommand;
        return loginCommand.execute(command, appState);
    }

    if (command.name == "logout"){
        LogoutCommand logoutCommand;
        return logoutCommand.execute(command, appState);
    }

    if (command.name == "mkgrp"){
        MkGrpCommand mkGrpCommand;
        return mkGrpCommand.execute(command, appState);
    }

    if (command.name == "rmgrp"){
        RmGrpCommand rmGrpCommand;
        return rmGrpCommand.execute(command, appState);
    }

    if (command.name == "mkusr"){
        MkUsrCommand mkUsrCommand;
        return mkUsrCommand.execute(command, appState);
    }

    if (command.name == "rmusr"){
        RmUsrCommand rmUsrCommand;
        return rmUsrCommand.execute(command, appState);
    }

    if (command.name == "chgrp"){
        ChGrpCommand chGrpCommand;
        return chGrpCommand.execute(command, appState);
    }

    if (command.name == "mkdir"){
        MkDirCommand mkDirCommand;
        return mkDirCommand.execute(command, appState);
    }

    if (command.name == "mkfile"){
        MkFileCommand mkFileCommand;
        return mkFileCommand.execute(command, appState);
    }

    if (command.name == "cat"){
        CatCommand catCommand;
        return catCommand.execute(command, appState);
    }

    if (command.name == "rep"){
        RepCommand repCommand;
        return repCommand.execute(command, appState);
    }

    return {false, "Error: comando no reconocido " + command.name + "."};
}


//Inicia el servidor
int main(){

    crow::App<crow::CORSHandler> app;

    //configura cors
    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors.global().headers("Content-Type").methods("GET"_method, "POST"_method, "OPTIONS"_method).origin("*");


    //verifica que el servidor este activo
    CROW_ROUTE(app, "/api/health")
    ([](){

        crow::json::wvalue response;

        response["success"] = true;
        response["message"] = "Servidor MIA activo.";

        return crow::response(200, response);
    });


    //analiza y ejecuta comandos
    CROW_ROUTE(app, "/api/analyze").methods(crow::HTTPMethod::POST)
    ([](const crow::request& request){

        crow::json::wvalue response;
        vector<string> messages;

        //lee json recibido
        crow::json::rvalue body = crow::json::load(request.body);

        if (!body){
            response["success"] = false;
            response["messages"] = vector<string>{"Error: cuerpo JSON no valido."};

            return crow::response(400, response);
        }

        //verifica campo input
        if (!body.has("input")){
            response["success"] = false;
            response["messages"] = vector<string>{"Error: falta el campo input."};

            return crow::response(400, response);
        }

        string inputText = body["input"].s();

        if (inputText.empty()){
            response["success"] = false;
            response["messages"] = vector<string>{"Error: no se ingresaron comandos."};

            return crow::response(400, response);
        }

        CommandToken tokenizer;

        //tokeniza todo el texto
        TokenizeResult tokenResult = tokenizer.tokenize(inputText);

        bool allSuccess = true;

        //guarda errores lexicos
        for (const string& error : tokenResult.errors){
            messages.push_back(error);
            allSuccess = false;
        }

        CommandParser parser;

        //convierte tokens en comandos
        ParseResult parseResult = parser.parse(tokenResult.tokens);

        //guarda errores del parser
        for (const string& error : parseResult.errors){
            messages.push_back(error);
            allSuccess = false;
        }

        //ejecuta comandos obtenidos
        for (const ParsedCommand& command : parseResult.commands){

            //muestra comentarios
            if (command.isComment){
                messages.push_back(command.commentText);
                continue;
            }

            //ignora comando vacio
            if (command.name.empty()){
                continue;
            }

            ValidationResult result = executeCommand(command);

            messages.push_back(result.message);

            if (!result.success){
                allSuccess = false;
            }
        }

        response["success"] = allSuccess;
        response["messages"] = messages;

        return crow::response(200, response);
    });


    cout << "Servidor MIA ejecutandose en http://localhost:2611" << endl;

    app.port(2611).multithreaded().run();

    return 0;
}