#pragma once
#include<iostream>
#include<vector>
#include<shard.h>

int main(int argc, char* argv[]) {
    
    std::vector<std::string> args;
    args.reserve(argc);
    
    for(int i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }

    shard::handleCommand(args);

    return 0;
}