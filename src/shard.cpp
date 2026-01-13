#include<shard.hpp>
#include<iostream>
#include<json.hpp>
#include<fstream>

std::filesystem::path getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::filesystem::path(buffer).parent_path();
}

void shard::handleCommand(args cmdArgs) {

    //cmdArgs[0] is always "shard"
    //cmdArgs[1] the command we want to listen to

    //we check if cmdArgs[1] is a shard command (ie, --config)
    for(auto& command : commands) {
        if(command.name == cmdArgs[1]) {
            command.function(cmdArgs);
            return;
        }
    }

    //we checked above if cmdArgs[1] is a shard command
    //if are here, that means it is not. now check if 
    //it is a user created command
    std::ifstream inFile(getExecutablePath() / "config.json");
    nlohmann::json configJson;
    inFile >> configJson;

    std::string currentDir = std::filesystem::current_path().string();
    //TODO: add proper error handling and logging
    if(!configJson.contains("directories")) return;
    if(!configJson["directories"].contains(currentDir)) return;
    if(!configJson["directories"][currentDir].contains(cmdArgs[1])) return;

    std::string dispatchedCommand = configJson["directories"][currentDir][cmdArgs[1]];
    std::system(dispatchedCommand.c_str());

    std::cout << "Command not found" << std::endl;
}