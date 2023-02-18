#pragma once
#include <dpp/dpp.h>
#include <string>
#include <map>
#include "eventhandle.hpp"

using namespace dpp;


extern void handleChallengeSubmit(user userId, snowflake challengeId, std::string gameName, std::string guildName, cluster& bot,const form_submit_t& event);
extern evt::eventhandle * handler;

command_option getScopeChoice() {
	return (command_option(co_string,"effectglobal","What should this command effect (defaults to only this)",false)
		.add_choice(command_option_choice("affect only this server","this"))
		.add_choice(command_option_choice("affect only global setting","global"))
		.add_choice(command_option_choice("affect both","both"))
		.add_choice(command_option_choice("affect all servers and global","all"))
		.add_choice(command_option_choice("affect all servers, but not global","allbut"))
	);
}

namespace botCmds {


dpp::slashcommand infoDef() {
	return dpp::slashcommand()
		.set_name("info")
		.set_description("info on the bot");
}





}
