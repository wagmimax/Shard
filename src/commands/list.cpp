#include<shard.hpp>
#include<fstream>
#include<json.hpp>

void shard::list(args cmdArgs) {
    //available commads:
    //shard --list
    //shard --list all

    //incorrect usage
    if(cmdArgs.size() != 2 && cmdArgs.size() != 3) {
        std::cout << "shard --list <optional {all} flag>" << std::endl;
    }

    if(!std::filesystem::exists(getExecutablePath() / "config.json")) {
        std::cout << "Must run \"shard --config\" first" << std::endl;
        return;
    }
    std::fstream inFile(getExecutablePath() / "config.json");
}