#include "crow.h"
#include "crow/middlewares/cors.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "analysis/CommandParser.hpp"
#include "analysis/CommandToken.hpp"

#include "commands/FDiskCommand.hpp"
#include "commands/MkDiskCommand.hpp"
#include "commands/MkFileCommand.hpp"
#include "commands/MkFsCommand.hpp"
#include "commands/MkUsrCommand.hpp"
#include "commands/MountCommand.hpp"
#include "commands/RmDiskCommand.hpp"
#include "commands/RmUsrCommand.hpp"

#include "simulation/SimulState.hpp"
#include "validation/ValidationResult.hpp"

using namespace std;


//verifica si la linea esta vacia
bool emptyLine(const string& line){
    for (char character : line){
        if (character != ' ' && character != '\t' && character != '\r'){
            return false;
        }
    }

    return true;
}


//ejecuta el comando que corresponde
ValidationResult executeCommand(const ParsedCommand& command, SimulState& simulState){

    //MkDisk
    if (command.name == "mkdisk"){
        MkDiskCommand mkDiskCommand;
        return mkDiskCommand.execute(command, simulState);
    }

    //RmDisk
    if (command.name == "rmdisk"){
        RmDiskCommand rmDiskCommand;
        return rmDiskCommand.execute(command, simulState);
    }

    //FDisk
    if (command.name == "fdisk"){
        FDiskCommand fdiskCommand;
        return fdiskCommand.execute(command, simulState);
    }

    //Mount
    if (command.name == "mount"){
        MountCommand mountCommand;
        return mountCommand.execute(command, simulState);
    }

    //MkFs
    if (command.name == "mkfs"){
        MkFsCommand mkFsCommand;
        return mkFsCommand.execute(command, simulState);
    }

    //MkUsr
    if (command.name == "mkusr"){
        MkUsrCommand mkUsrCommand;
        return mkUsrCommand.execute(command, simulState);
    }

    //RmUsr
    if (command.name == "rmusr"){
        RmUsrCommand rmUsrCommand;
        return rmUsrCommand.execute(command, simulState);
    }

    //MkFile
    if (command.name == "mkfile"){
        MkFileCommand mkFileCommand;
        return mkFileCommand.execute(command, simulState);
    }

    return {
        false,
        "Comando no reconocido: " + command.name
    };
}


int main(){
    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors.global()
        .origin("*")
        .headers("Content-Type")
        .methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS);

    SimulState simulState("202405047");


    //GET
    CROW_ROUTE(app, "/api/health")([](){
        crow::json::wvalue body;
        body["status"] = "ok";

        return crow::response(200, body);
    });


    //POST
    CROW_ROUTE(app, "/api/analyze").methods(crow::HTTPMethod::POST)([&simulState](const crow::request& request){
        crow::json::rvalue requestBody = crow::json::load(request.body);


        if (!requestBody){
            crow::json::wvalue body;
            body["success"] = false;

            crow::json::wvalue::list messages;
            messages.emplace_back("Error: el contenido recibido no es un JSON valido.");

            body["messages"] = std::move(messages);

            return crow::response(400, body);
        }


        if (!requestBody.has("input")){
            crow::json::wvalue body;
            body["success"] = false;

            crow::json::wvalue::list messages;
            messages.emplace_back("Error: no se recibio texto para analizar.");

            body["messages"] = std::move(messages);

            return crow::response(400, body);
        }


        //input desde front
        string commandText = requestBody["input"].s();


        //vector de mensajes por salida
        vector<string> outputMessages;
        bool hasErrors = false;

        //recorre linea*linea
        stringstream commandStream(commandText);
        string currentLine;


        //bucle de analisis
        while (getline(commandStream, currentLine)){

            //conserva linea vacia
            if (emptyLine(currentLine)){
                outputMessages.push_back("");
                continue;
            }


            //analisis lexico
            CommandToken commandToken;
            TokenizeResult tokenResult = commandToken.tokenize(currentLine);

            if (!tokenResult.errors.empty()){
                hasErrors = true;

                for (const string& lexicalError : tokenResult.errors){
                    outputMessages.push_back(lexicalError);
                }

                continue;
            }


            //analisis sintactico
            CommandParser commandParser;
            ParseResult parseResult = commandParser.parse(tokenResult.tokens);

            if (!parseResult.errors.empty()){
                hasErrors = true;

                for (const string& syntaxError : parseResult.errors){
                    outputMessages.push_back(syntaxError);
                }

                continue;
            }


            //recorre comandos parseados
            for (const ParsedCommand& parsedCommand : parseResult.commands){

                //si es comentario solo lo muestra
                if (parsedCommand.isComment){
                    outputMessages.push_back(parsedCommand.commentText);
                    continue;
                }

                ValidationResult commandResult = executeCommand(parsedCommand, simulState);
                outputMessages.push_back(commandResult.message);

                if (!commandResult.success){
                    hasErrors = true;
                }
            }
        }


        if (outputMessages.empty()){
            outputMessages.push_back("No se encontraron comandos para analizar.");
        }


        //json
        crow::json::wvalue::list jsonMessages;

        for (const string& message : outputMessages){
            jsonMessages.emplace_back(message);
        }

        crow::json::wvalue body;
        body["success"] = !hasErrors;
        body["messages"] = std::move(jsonMessages);


        return crow::response(200, body);
    });


    cout << "Servidor: http://localhost:2611\n";
    cout << "GET  /api/health\n";
    cout << "POST /api/analyze\n";

    app.port(2611).multithreaded().run();

    return 0;
}