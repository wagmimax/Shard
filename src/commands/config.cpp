#include<shard.hpp>
#include<json.hpp>
#include<fstream>

static void setShardCommand(shard::args cmdArgs) {

    //cmdArgs[0] shard         
    //cmdArgs[1] --config                              all previous commands have checked
    //cmdArgs[2] set                                   <-- up to here. error check the rest
    //cmdArgs[3] {user defined name for the command}
    //cmdArgs[4] as
    //cmdArgs[5] {actual command}

    if(cmdArgs.size() != 6 || cmdArgs[4] != "as") {
        std::cout << "shard --config set <name> as <command>" << std::endl;
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

static void createConfigJson(std::filesystem::path path) {
    std::ofstream configJson(path / "config.json");
    std::cout << "Created Config File at " << path / "config.json" << std::endl;

    nlohmann::json json;
    json["directories"];

    configJson << json;
}

static constexpr std::array configCommands = {shard::Command{"set", }};

void shard::config(args cmdArgs) {


    //check if config file exists. if not, create one
    if (!std::filesystem::exists(getExecutablePath() / "config.json")) {
        createConfigJson(getExecutablePath());
    }

    setShardCommand(cmdArgs);
}