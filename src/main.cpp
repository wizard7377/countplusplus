#include <dpp/dpp.h>
#include <map>
#include <variant>
#include <cctype>
#include <config.hpp>
#include <iostream>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include "eventhandle.hpp"
#include <cmath>
#include <chrono>  
#include <filesystem>
#include <nlohmann/json.hpp>
#include "commandHandle.hpp"


using namespace dpp;
using json = nlohmann::json;
namespace fs = std::filesystem;


/*
 * All the command handlers
 */

evt::eventhandle * handler;



std::string getFullPath(std::string filePath) {
	return (fs::current_path() /= filePath);
}
std::string getFullPath(std::vector<std::string> filePath) {
	fs::path retPath = fs::current_path();
	for (auto sub: filePath) {
		retPath /= sub;
	}
	return retPath.string();
}







int main(int argc, char *argv[]) {
	std::ifstream jFile(getFullPath("secrets/config.json"));
	json gameconfig = json::parse(jFile)["DISCORD"];

	cluster bot((gameconfig["BOT_TOKEN"]),dpp::i_default_intents | dpp::i_message_content);
	


	try {
		handler = new evt::eventhandle(&bot);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		exit(0);
	}

	//createCommandHandle();
	
	
	bot.on_log(utility::cout_logger());

	if (argc != 0) {
		if (std::string(argv[0]) == "1") {
			
		}
	}
	
	

	
	
	

	bot.on_ready([&bot](const ready_t & event) {
        if (run_once<struct register_bot_commands>()) {
			
			bot.global_command_create(botCmds::infoDef());
			
	}
    });
	
	
	
	bot.start(st_wait);
		

	



}
