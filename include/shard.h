#pragma once
#include<unordered_map>
#include<string>
#include<array>
#include<iostream>

namespace shard {    

    using args = const std::vector<std::string>&;

    void install(args);
    void config(args);
    void list(args);

    struct Command {
        std::string_view name;
        void (*function)(args);
    };

    constexpr std::array commands = {
        Command{"install", &install},
        Command{"config", &config},
        Command{"list", &list}
    };

    void handleCommand(args);
};