#include<shard.hpp>
#include<fstream>
#include<json.hpp>
#include<iomanip>

void shard::list(args cmdArgs) {
    //available commads:
    //shard --list
    //shard --list all

    //incorrect usage
    if(cmdArgs.size() != 2 && cmdArgs.size() != 3 && cmdArgs[2] != "all") {
        std::cout << "shard --list <optional {all} flag>" << std::endl;
    }

    if(!std::filesystem::exists(getExecutablePath() / "config.json")) {
        std::cout << "Must run \"shard --config\" first" << std::endl;
        return;
    }

    std::fstream inFile(getExecutablePath() / "config.json");
    nlohmann::json configJson;
    inFile >> configJson;

    //shard --list
    if(cmdArgs.size() == 2) {
        auto currentPath = std::filesystem::current_path();

        if(!configJson["directories"].contains(currentPath.string())) {
            std::cout << "No commands in this directory" << std::endl;
            return;
        }

        std::cout << std::left << std::setw(15) << "Name" 
                  << std::left << std::setw(15) << "Command" << std::endl;
        std::cout << "----------------------" << std::endl;

        for(const auto& [key, value] : configJson["directories"][currentPath.string()].items()) {
            std::cout << std::left << std::setw(15) << key
                      << std::left << std::setw(15) << value.dump() << std::endl;
        }


    }

    


    
}