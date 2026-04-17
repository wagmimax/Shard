#pragma once

#include<string>
#include<array>
#include<vector>
#include<iostream>
#include<filesystem>

#ifdef __WIN32
#include<windows.h>
#elif __linux__
#include<unistd.h>
#include<climits>
#endif

std::filesystem::path getExecutablePath();

namespace shard {    

    using args = const std::vector<std::string>&;

    void config(args);
    void list(args);

    struct Command {
        std::string_view name;
        void (*function)(args);
    };

    constexpr std::array commands = {
        Command{"--config", &config},
        Command{"--list", &list}
    };

    void handleCommand(args);
};
