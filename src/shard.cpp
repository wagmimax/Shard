#include<shard.hpp>
#include<iostream>

std::filesystem::path getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::filesystem::path(buffer).parent_path();
}

void shard::handleCommand(args cmdArgs) {
    for(auto& command : commands) {
        if(command.name == cmdArgs[1]) {
            command.function(cmdArgs);
            return;
        }
    }

    std::cout << "Command not found" << std::endl;
}