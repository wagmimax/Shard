#include<shard.h>
#include<iostream>

void shard::handleCommand(args cmdArgs) {
    for(auto& command : commands) {
        if(command.name == cmdArgs[1]) {
            command.function(cmdArgs);
            return;
        }
    }

    std::cout << "Invalid command" << std::endl;
}