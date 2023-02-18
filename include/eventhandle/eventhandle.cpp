#include <thread>
#include <string>
#include <dpp/dpp.h>
#include <functional>
#include <unordered_map>
#include <iostream>
#include "gamenums.hpp"
#include "eventhandle.hpp"

//extern void handleChallengeSubmit(user userId, snowflake challengeId, std::string gameName, std::string guildName, cluster& bot,const form_submit_t& event);

using namespace dpp;

namespace evt {
	
eventhandle::eventhandle(cluster * bot) {
	this->testCon = new mData::dataHandle();
	
	bot->on_select_click([this](const auto& event) {
		try {
			std::thread([this,event] { try { this->selectCmds.at(event.custom_id)(event); } catch (...) {} } ).detach();
		} catch (...) {
			std::cout << "An error has occured" << std::endl;
		}
	});
	bot->on_button_click([this](const auto& event) {
		try {
			std::thread([this,event] { (this->buttonCmds.at(event.custom_id))(event); }).detach();
		} catch (...) {
			std::cout << "An error has occured" << std::endl;
		}
	});
	bot->on_form_submit([this](const auto& event) {
		try {
			std::thread([this,event] { this->formCmds.at(event.custom_id)(event); }).detach();
		} catch (...) {
			std::cout << "An error has occured" << std::endl;
		}
	});
	bot->on_slashcommand([this,bot](const auto& event) {
		try {
			//uint64_t retId = std::get<uint64_t>(this->testCon->getUser((uint64_t)(event.command.get_issuing_user().id))[0]);
			//uint64_t retIdT = std::get<uint64_t>(this->testCon->getUser(((uint64_t)(event.command.get_issuing_user().id)),((uint64_t)(event.command.get_guild().id)))[0]);
			//std::cout << std::endl << "Cur user is: " << std::to_string(retId) << " and: " << retIdT << std::endl << std::endl;
			std::thread([this,event,bot] { this->slashCmds.at(event.command.get_command_name())(event); }).detach();
		} catch (...) {
			std::cout << "An error has occured" << std::endl;
		}
	});
	
	

	this->addSlashCmd("info",[bot](const slashcommand_t &event) {
		event.reply("This bot is for playing two player games, and it's source code may be found at https://github.com/wizard7377/countplusplus.git");
	});
	
	
		


		



	std::cout << "Event handelers succesfully started" << std::endl;

}
//bool eventhandle::addSelectCmd(std::string compid,std::function<void(const select_click_t&)> newCmd) {
bool eventhandle::addSelectCmd(std::string compid,std::function<void(const select_click_t&)> newCmd) {
	try { this->selectCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::addSlashCmd(std::string compid,std::function<void(const slashcommand_t&)> newCmd) {
	try { this->slashCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::addFormCmd(std::string compid,std::function<void(const form_submit_t&)> newCmd) {
	try { this->formCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::addButtonCmd(std::string compid,std::function<void(const button_click_t&)> newCmd) {
	try { this->buttonCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}




bool eventhandle::deleteSelectCmd(std::string compid) {
	try { this->selectCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::deleteSlashCmd(std::string compid) {
	try { this->slashCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::deleteFormCmd(std::string compid) {
	try { this->slashCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::deleteButtonCmd(std::string compid) {
	try { this->buttonCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}


}
