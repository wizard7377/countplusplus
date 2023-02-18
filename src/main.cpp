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


using namespace dpp;
using json = nlohmann::json;



/*
 * All the command handlers
 */

evt::eventhandle * handler;











int main(int argc, char *argv[]) {
	std::ifstream jFile(getFullPath("secrets/config.json"));
	json gameconfig = json::parse(jFile)["DISCORD"];

	cluster bot(gameconfig["BOT_TOKEN"]);
	


	try {
		handler = new evt::eventhandle(&bot);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		exit(0);
	}

	createCommandHandle();
	
	
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