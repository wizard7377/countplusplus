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

dpp::slashcommand setDef() {
	return dpp::slashcommand()
		.set_name("countrules")
		.set_description("Change rules for counting currently (NOTE, WILL RESET COUNT)")
		.add_option(command_option(co_number,"start","Value count should start at"))
		.add_option(command_option(co_number,"step","Value count should increment by"))
		.add_option(command_option(co_integer,"lives","Number of lives user should have"))
		.set_default_permissions(0)
		.set_dm_permission(false);
}

dpp::slashcommand resetDef() {
	return dpp::slashcommand()
		.set_name("reset")
		.set_description("reset lives and count to start (KINDA OBVIOUS BUT THIS WILL RESET THE COUNT)")
		.set_default_permissions(0)
		.set_dm_permission(false);
}
dpp::slashcommand chanDef() {
	return dpp::slashcommand()
		.set_name("channelset")
		.set_description("Set default channel for all things Count++ related")
		.add_option(command_option(co_channel,"channel","channel you would like to set it to (defaults to current channel)",false))
		.set_default_permissions(0)
		.set_dm_permission(false);
}





}
