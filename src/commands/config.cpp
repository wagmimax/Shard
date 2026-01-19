#include<shard.hpp>
#include<json.hpp>
#include<fstream>

//create and add a new command to config.json. new commands are automatically set to the current directory you are in
static void setShardCommand(shard::args cmdArgs) {
    //mock command:
    //shard --config set <name> as <command>

    //cmdArgs[0] shard         
    //cmdArgs[1] --config                              all previous commands have checked
    //cmdArgs[2] set                                   <-- up to here. error check the rest
    //cmdArgs[3] {user defined name for the command}
    //cmdArgs[4] as
    //cmdArgs[5] {actual command}

    if(cmdArgs.size() != 6 || cmdArgs[4] != "as") {
        std::cout << "shard --config set <name> as <command>" << std::endl;
        return;
    }

    //load existing config json
    std::ifstream inFile(getExecutablePath() / "config.json");
    nlohmann::json configJson;
    inFile >> configJson;

    //when setting new commands, they are instantiated to the current directory
    std::string currentDir = std::filesystem::current_path().string();

    //the json we will append to configJson, holding our new command
    nlohmann::json newCommand;
    newCommand["directories"][currentDir][cmdArgs[3]] = cmdArgs[5];

    //update with the new command
    configJson.update(newCommand, true);

    //truncate and write to config.json
    std::ofstream outFile(getExecutablePath() / "config.json", std::ios::trunc);
    outFile << configJson.dump(4);

    outFile.close();
    inFile.close();
}

//remove a shard command from the config
static void deleteShardCommand(shard::args cmdArgs) {
    //mock command:
    //shard --config delete <name>

    //cmdArgs[0] shard         
    //cmdArgs[1] --config                           
    //cmdArgs[2] delete                            
    //cmdArgs[3] {user defined name for the command}

    if(cmdArgs.size() != 4) {
        std::cout << "shard --config delete <name>" << std::endl;
        return;
    }

    //load existing config json
    std::ifstream inFile(getExecutablePath() / "config.json");
    nlohmann::json configJson;
    inFile >> configJson;

    //delete the command
    std::string command = cmdArgs[3];
    configJson["directories"][std::filesystem::current_path().string()].erase(command);

    //truncate and write to config.json
    std::ofstream outFile(getExecutablePath() / "config.json", std::ios::trunc);
    outFile << configJson.dump(4);

    outFile.close();
    inFile.close();
}

//delete directories and their commands if they no longer exist
static void purgeShardCommands(shard::args cmdArgs) {
    //mock command:
    //shard --config purge
    
    if(cmdArgs.size() != 3) {
        std::cout << "shard --config purge" << std::endl;
        return;
    }

    //load config file
    std::ifstream inFile(getExecutablePath() / "config.json");
    nlohmann::json configJson;
    inFile >> configJson;

    //iterate over all directories, and check if they exist
    std::cout << "\n";
    for(auto& [directory, other] : configJson["directories"].items()) {
        if(!std::filesystem::exists(directory)) {
            std::cout << "Purged: " << directory << std::endl;
            configJson["directories"].erase(directory);
            
        }
    }

    std::ofstream outFile(getExecutablePath() / "config.json", std::ios::trunc);
    outFile << configJson.dump(4);

    outFile.close();
    inFile.close();
}

//upon first time calling shard --config
static void createConfigJson(std::filesystem::path path) {
    std::ofstream configJson(path / "config.json");
    std::cout << "Created Config File at " << path / "config.json" << std::endl;

    nlohmann::json json;
    json["directories"];

    configJson << json;
}

static constexpr std::array configCommands = {shard::Command{"set", &setShardCommand},
                                              shard::Command{"delete", &deleteShardCommand},
                                              shard::Command{"purge", &purgeShardCommands}};

void shard::config(args cmdArgs) {

    //check if config file exists. if not, create one
    if (!std::filesystem::exists(getExecutablePath() / "config.json")) {
        createConfigJson(getExecutablePath());
    }

    for(auto& command : configCommands) {
        if(command.name == cmdArgs[2]) {
            command.function(cmdArgs);
        }
    }
}